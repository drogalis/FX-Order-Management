
#include <fx_utilities.h>

#include <string>
#include <exception>
#include <iostream>

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <keychain.h>

namespace std {

FXUtilities::FXUtilities () { }

FXUtilities::~FXUtilities () { }

void FXUtilities::setup_password_first_time(string account_type, string username) {
    string test_account_password;
    string account_password;    
    string password;
    
    string service_id_test = "Test_Account";
    string service_id_live = "Live_Account";

    string package_test = "com.gain_capital_forex.test_account";
    string package_live = "com.gain_capital_forex.live_account";
  
    keychain::Error error = keychain::Error{};
    // Prompt Keyring Unlock
    keychain::setPassword("Forex_Keychain_Unlocker", "", "", "", error);
    if (error) {
        std::cerr << error.message << std::endl;
        std::terminate();
    }

    if (account_type == "PAPER") {
        error = keychain::Error{};
        password = keychain::getPassword(package_test, service_id_test, username, error);
        
        if (error.type == keychain::ErrorType::NotFound) {
            std::cout << "Test Account password not found. Please input password: ";
            cin >> test_account_password;

            // Test Password Setup
            keychain::setPassword(package_test, service_id_test, username, test_account_password, error);
            if (error) {
                std::cerr << "Test Account " << error.message << std::endl;
                std::terminate();
            }
        } else if (error) {
            std::cerr << error.message << std::endl;
            std::terminate();
        }
    }
    // -------------------------------
    if (account_type == "LIVE") {
        error = keychain::Error{};
        password = keychain::getPassword(package_live, service_id_live, username, error);
        
        if (error.type == keychain::ErrorType::NotFound) {
            std::cout << "Live Account password not found. Please input password: ";
            cin >> account_password;

            // Live Password Setup
            keychain::setPassword(package_live, service_id_live, username, account_password, error);
            if (error) {
                std::cerr << "Live Account " << error.message << std::endl;
                std::terminate();
            }
        } else if (error) {
            std::cerr << error.message << std::endl;
            std::terminate();
        }
    }
}

void FXUtilities::init_logging(string working_directory) {
    string date = get_todays_date();
    string file_name = working_directory + "/" + date + "_FX_Order_Management.log";

    boost::log::add_file_log(        
        boost::log::keywords::file_name = file_name,                                                                   
        boost::log::keywords::format = "[%TimeStamp%]: %Message%",
        boost::log::keywords::auto_flush = true
    );

    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::debug
    );

    boost::log::add_common_attributes();
}

string FXUtilities::get_todays_date() {
    time_t t;
    struct tm *tmp;
    char DATE_TODAY[50];
    time( &t );
    tmp = localtime( &t );
     
    strftime(DATE_TODAY, sizeof(DATE_TODAY), "%Y_%m_%d", tmp);

    return DATE_TODAY;
}

}