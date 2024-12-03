#include "validators.hpp"

#include "consts.hpp"
#include "errors.hpp"

namespace RobinID::utils::validators {

bool CheckSize(std::string_view value, int min, int max) {
    const int length = value.length();
    return min <= length && length <= max;
}

void ValidateEmail(std::string_view email) {
    if (email.empty()) {
        throw utils::errors::ValidationError{consts::kEmailField, consts::kEmpty};
    }

    if (!std::regex_match(email.data(), consts::kEmailPattern)) {
        throw utils::errors::ValidationError{consts::kEmailField, consts::kInvalid};
    }
}

void ValidateUsername(std::string_view username) {
    if (!std::regex_match(username.data(), consts::kUsernamePattern)) {
        throw utils::errors::ValidationError{consts::kUsernameField, consts::kInvalid};
    }

    if (!CheckSize(username, consts::kUsernameLengthMin, consts::kUsernameLengthMax)) {
        throw utils::errors::ValidationError{
            consts::kUsernameField, fmt::format(consts::kLengthErrorMessage, consts::kUsernameField,
                                                consts::kUsernameLengthMin, consts::kUsernameLengthMax)};
    }
}

void ValidatePassword(std::string_view password) {
    if (!std::regex_match(password.data(), consts::kPasswordPattern)) {
        throw utils::errors::ValidationError{consts::kPasswordField, consts::kInvalid};
    }

    if (!CheckSize(password, consts::kPasswordLengthMin, consts::kPasswordLengthMax)) {
        throw utils::errors::ValidationError{
            consts::kPasswordField, fmt::format(consts::kLengthErrorMessage, consts::kPasswordField,
                                                consts::kPasswordLengthMin, consts::kPasswordLengthMax)};
    }
}

}  // namespace RobinID::utils::validators