#include <cpprest/http_client.h>
#include <cpprest/oauth2.h>
#include <cpprest/ws_client.h>
#include <cpprest/json.h>
#include <iostream>
#include <fstream>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
    // Replace these values with your bot's information
    const utility::string_t clientId = U("YOUR_CLIENT_ID");
    const utility::string_t clientSecret = U("YOUR_CLIENT_SECRET");
    const utility::string_t botToken = U("YOUR_BOT_TOKEN");

    uri_builder builder(U("https://discord.com/api/oauth2/token"));

    // Set up OAuth2 request parameters
    http_request token_request(methods::POST);
    token_request.headers().set_content_type(U("application/x-www-form-urlencoded"));
    token_request.set_body(U("grant_type=client_credentials"));
    token_request.headers().set_basic_auth(clientId, clientSecret);

    // Send the OAuth2 request to get the access token
    http_client token_client(builder.to_uri());
    auto token_response = token_client.request(token_request).get();

    // Extract the access token from the response
    web::json::value token_json = token_response.extract_json().get();
    utility::string_t access_token = token_json[U("access_token")].as_string();

    // Now you can use the access token to make requests to the Discord API
    http_client discord_api(U("https://discord.com/api/v10"));

    // Replace USER_ID with the actual Discord user ID
    uri_builder user_activity_endpoint(U("/users/USER_ID"));
    user_activity_endpoint.append_query(U("limit"), U("1")); // Limit to 1 activity (most recent)

    http_request activity_request(methods::GET);
    activity_request.headers().set_authorization(U("Bot ") + botToken);

    // Send the request to get user activity
    auto activity_response = discord_api.request(activity_request).get();
    web::json::value activity_json = activity_response.extract_json().get();

    // Parse and display the user's Spotify activity
    if (activity_json.has_field(U("activities"))) {
        auto activities = activity_json[U("activities")].as_array();
        for (const auto& activity : activities) {
            utility::string_t activity_type = activity[U("type")].as_string();
            if (activity_type == U("LISTENING") && activity[U("name")].as_string() == U("Spotify")) {
                // Handle Spotify activity, e.g., get the track name, artist, etc.
                utility::string_t track_name = activity[U("details")].as_string();
                utility::string_t artist_name = activity[U("state")].as_string();

                // Print to console
                std::wcout << L"Currently listening to Spotify: " << track_name << L" by " << artist_name << std::endl;

                // Save to a text file on the desktop
                std::wofstream outfile("C:\\Users\\YourUsername\\Desktop\\spotify_activity.txt", std::ios::app);
                if (outfile.is_open()) {
                    outfile << L"Track: " << track_name << L", Artist: " << artist_name << std::endl;
                    outfile.close();
                    std::wcout << L"Results saved to desktop: spotify_activity.txt" << std::endl;
                } else {
                    std::wcerr << L"Unable to open file for writing." << std::endl;
                }
            }
        }
    }

    return 0;
}
