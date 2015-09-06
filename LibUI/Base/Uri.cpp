#include "stdafx.h"
#include "Uri.h"

#include <ctype.h>
#include <regex>

namespace base {

namespace {

	std::string submatch(const std::cmatch& m, size_t idx) {
		auto& sub = m[idx];
		return std::string(sub.first, sub.second);
	}

template <class String>
void toLower(String& s) {
  for (auto& c : s) {
    c = tolower(c);
  }
}

}  // namespace

Uri::Uri(const std::string& str) : hasAuthority_(false), port_(0) {
  static const std::regex uriRegex(
      "([a-zA-Z][a-zA-Z0-9+.-]*):"  // scheme:
      "([^?#]*)"                    // authority and path
      "(?:\\?([^#]*))?"             // ?query
      "(?:#(.*))?");                // #fragment
  static const std::regex authorityAndPathRegex("//([^/]*)(/.*)?");

  std::cmatch match;
  if (!std::regex_match(str.c_str(), match, uriRegex)) {
	  std::string arg = "invalid URI ";
	  arg += str;
    throw std::invalid_argument(arg);
  }

  scheme_ = match[1];
  toLower(scheme_);

  const char* authorityAndPathBegin = match[2].first;
  const char* authorityAndPathEnd = match[2].second; 
  std::cmatch authorityAndPathMatch;
  if (!std::regex_match(authorityAndPathBegin,
						 authorityAndPathEnd,
                          authorityAndPathMatch,
                          authorityAndPathRegex)) {
    // Does not start with //, doesn't have authority
    hasAuthority_ = false;
	path_ = std::string(authorityAndPathBegin, authorityAndPathEnd);
  } else {
    static const std::regex authorityRegex(
        "(?:([^@:]*)(?::([^@]*))?@)?"  // username, password
        "(\\[[^\\]]*\\]|[^\\[:]*)"     // host (IP-literal (e.g. '['+IPv6+']',
                                       // dotted-IPv4, or named host)
        "(?::(\\d*))?");               // port

    auto authority = authorityAndPathMatch[1];
    std::cmatch authorityMatch;
    if (!std::regex_match(authority.first,
                            authority.second,
                            authorityMatch,
                            authorityRegex)) {
		std::string arg = "invalid URI authority";
		arg += authority.str();
		throw std::invalid_argument(arg);
    }
    auto port = authorityMatch[4];
    if (port.length() > 0) {
		port_ = std::stol(port.str());
    }

    hasAuthority_ = true;
    username_ = submatch(authorityMatch, 1);
    password_ = submatch(authorityMatch, 2);
    host_ = submatch(authorityMatch, 3);
    path_ = submatch(authorityAndPathMatch, 2);
  }

  query_ = submatch(match, 3);
  fragment_ = submatch(match, 4);
}

std::string Uri::authority() const {
	std::string result;

  // Port is 5 characters max and we have up to 3 delimiters.
  result.reserve(host().size() + username().size() + password().size() + 8);

  if (!username().empty() || !password().empty()) {
    result.append(username());

    if (!password().empty()) {
      result.push_back(':');
      result.append(password());
    }

    result.push_back('@');
  }

  result.append(host());

  if (port() != 0) {
    result.push_back(':');
	result.append(std::to_string(port()));   
  }

  return result;
}


std::string Uri::toString() const
{
	std::string str;
	if (hasAuthority_) {
		str = scheme_ + "://";
		if (!password_.empty()) {
			str += (username_+":"+password_+"@");
		}
		else if (!username_.empty()) {
			str += (username_ + "@");
		}
		str += host_;
		if (port_ != 0) {
			str += ":" + std::to_string(port_);			
		}
	}
	else {
		str += scheme_ + ":";
	}
	str += path_;
	if (!query_.empty()) {
		str += "?" + query_;		
	}
	if (!fragment_.empty()) {
		str += "#" + fragment_;
	}
	return str;
}

std::string Uri::hostname() const {
  if (host_.size() > 0 && host_[0] == '[') {
    // If it starts with '[', then it should end with ']', this is ensured by
    // regex
    return host_.substr(1, host_.size() - 2);
  }
  return host_;
}

const std::vector<std::pair<std::string, std::string>>& Uri::getQueryParams() {
  if (!query_.empty() && queryParams_.empty()) {
    // Parse query string
    static const std::regex queryParamRegex(
        "(^|&)" /*start of query or start of parameter "&"*/
        "([^=&]*)=?" /*parameter name and "=" if value is expected*/
        "([^=&]*)" /*parameter value*/
        "(?=(&|$))" /*forward reference, next should be end of query or
                      start of next parameter*/);
    std::cregex_iterator paramBeginItr(
        query_.data(), query_.data() + query_.size(), queryParamRegex);
    std::cregex_iterator paramEndItr;
    for (auto itr = paramBeginItr; itr != paramEndItr; itr++) {
      if (itr->length(2) == 0) {
        // key is empty, ignore it
        continue;
      }
      queryParams_.emplace_back(
          (*itr)[2].str(), // parameter name
          (*itr)[3].str() // parameter value
          );
    }
  }
  return queryParams_;
}

}  // namespace base
