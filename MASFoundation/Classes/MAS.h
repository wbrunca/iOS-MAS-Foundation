//
//  MAS.h
//  MASFoundation
//
//  Copyright (c) 2016 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

@import Foundation;

#import "MASConstants.h"
#import "MASClaims.h"


/**
 * The top level MAS object represents the Mobile App Services SDK in it's entirety.  It
 * is where the framework lifecycle begins, and ends if necessary.  It is the front 
 * facing class where many of the configuration settings for the SDK as a whole can be 
 * found and utilized.
 */
@interface MAS : NSObject



///--------------------------------------
/// @name Properties
///--------------------------------------

# pragma mark - Properties

/**
 *  Set the name of the configuration file.  This gives the ability to set the file's name
 *  to a custom value.
 *
 *  @param fileName The NSString name of the configuration file.
 */
+ (void)setConfigurationFileName:(NSString *_Nonnull)fileName;



/**
 *  Sets the MASGrantFlow property.  The default is MASGrantFlowClientCredentials.
 *
 *  @param grantFlow The MASGrantFlow.
 */
+ (void)setGrantFlow:(MASGrantFlow)grantFlow;



/**
 *  Returns current MASGrantFlow property.  The default is MASGrantFlowClientCredentials.
 *
 *  @return return MASGrantFlow of current type.
 */
+ (MASGrantFlow)grantFlow;



/**
 *  Sets BOOL indicator of PKCE (Proof KEy for Code Exchange) enabled or not for authorization process in Social Login, and Proximity Login.
 *  By default, PKCE is enabled and enforced in authorization process; it can be opted-out.
 *
 *  @since MAS Client SDK 1.4 and MAG/OTK 4.0 on April 2017 release.
 *  @dependency Minimum version of MAG/OTK 4.0 is required to successfully perform PKCE.  If the server side does not support PKCE, client side will still work without PKCE verification.
 *  @param enable BOOL value of indicating whether PKCE is enabled or not.
 */
+ (void)enablePKCE:(BOOL)enable;



/**
 *  Gets BOOL indicator of PKCE (Proof KEy for Code Exchange) enabled or not for authorization process in Social Login, and Proximity Login.
 *  By default, PKCE is enabled and enforced in authorization process; it can be opted-out.
 *
 *  @since MAS Client SDK 1.4 and MAG/OTK 4.0 on April 2017 release.
 *  @dependency Minimum version of MAG/OTK 4.0 is required to successfully perform PKCE.  If the server side does not support PKCE, client side will still work without PKCE verification.
 *  @return BOOL value of indicating whether PKCE is enabled or not.
 */
+ (BOOL)isPKCEEnabled;



/**
 *  Set a user login block to handle the case where the type set in 'setDeviceRegistrationType:(MASDeviceRegistrationType)'
 *  is 'MASDeviceRegistrationTypeUserCredentials'.  If it set to 'MASDeviceRegistrationTypeClientCredentials' this
 *  is not called.
 *
 *  @param login The MASUserLoginWithUserCredentialsBlock to receive the request for user credentials.
 */
+ (void)setUserLoginBlock:(MASUserLoginWithUserCredentialsBlock _Nullable)login;



/**
 *  Set a OTP channel selection block to handle the case where the channel for Two-factor authentication is required.
 *
 *  @param OTPChannelSelector The MASOTPChannelSelectionBlock to receive the request for OTP channels.
 */
+ (void)setOTPChannelSelectionBlock:(MASOTPChannelSelectionBlock _Nullable)OTPChannelSelector;



/**
 *  Set a OTP credentials block to handle the case where a Two-factor authentication is required.
 *
 *  @param oneTimePassword The MASOTPCredentialsBlock to receive the request for OTP credentials.
 */
+ (void)setOTPCredentialsBlock:(MASOTPCredentialsBlock _Nullable)oneTimePassword;



/**
 *  Sets the gateway monitoring block defined by the GatewayMonitorStatusBlock type.
 *  This block will be triggered when any change to the current monitoring status
 *  takes place with a MASGatewayMonitoringStatus.
 *
 *  The gateway monitoring status enumerated values are:
 *
 *      MASGatewayMonitoringStatusNotReachable
 *      MASGatewayMonitoringStatusReachableViaWWAN
 *      MASGatewayMonitoringStatusReachableViaWiFi
 *
 *  This is optional and it can be set to nil at any time to stop receiving the notifications.
 *
 *  @param monitor The MASGatewayMonitorStatusBlock that will receive the status updates.
 */
+ (void)setGatewayMonitor:(MASGatewayMonitorStatusBlock _Nullable)monitor;



/**
 *  Returns current MASState enumeration value.  The value can be used to determine which state SDK is currently at.
 *
 *  @return return MASState of current state.
 */
+ (MASState)MASState;


#ifdef DEBUG

/**
 *  Turn on or off the logging of the network activity with the Gateway.
 *
 *  @param enabled BOOL YES to turn on logging, NO to turn it off.
 */
+ (void)setGatewayNetworkActivityLogging:(BOOL)enabled;

#endif



///--------------------------------------
/// @name Start & Stop
///--------------------------------------

# pragma mark - Start & Stop

/**
 *  Starts the lifecycle of the MAS processes.  
 *
 *  Although an asynchronous block callback parameter is provided for response usage, 
 *  optionally you can set that to nil and the caller can observe the lifecycle 
 *  notifications instead.
 *
 *  This will load the last used JSON configuration from keychain storage.  If there was none,
 *  it will load from default JSON configuration file (msso_config.json)
 *  or JSON file with file name set through [MAS setConfigurationFileName:].
 *
 *  The MAS lifecycle notifications are:
 *
 *      MASWillStartNotification
 *      MASDidFailToStartNotification
 *      MASDidStartNotification
 *
 *  The application registration notifications are:
 *
 *      MASApplicationWillRegisterNotification
 *      MASApplicationDidFailToRegisterNotification
 *      MASApplicationDidRegisterNotification
 *
 *  @param completion An MASCompletionErrorBlock type (BOOL completed, NSError *error) that will
 *      receive a YES or NO BOOL indicating the completion state and/or an NSError object if there
 *      is a failure.
 */
+ (void)start:(MASCompletionErrorBlock _Nullable)completion;



/**
 *  Starts the lifecycle of the MAS processes.
 *
 *  Although an asynchronous block callback parameter is provided for response usage,
 *  optionally you can set that to nil and the caller can observe the lifecycle
 *  notifications instead.
 *
 *  This will load the default JSON configuration rather than from keychain storage; if the SDK was already initialized, this method will fully stop and re-start the SDK.
 *  The default JSON configuration file should be msso_config.json or file name defined through [MAS setConfigurationFileName:].
 *  This will ignore the JSON configuration in keychain storage and replace with the default configuration.
 *
 *  The MAS lifecycle notifications are:
 *
 *      MASWillStartNotification
 *      MASDidFailToStartNotification
 *      MASDidStartNotification
 *
 *  The application registration notifications are:
 *
 *      MASApplicationWillRegisterNotification
 *      MASApplicationDidFailToRegisterNotification
 *      MASApplicationDidRegisterNotification
 *
 *  @param shouldUseDefault Boolean value of using default configuration rather than the one in keychain storage.
 *  @param completion An MASCompletionErrorBlock type (BOOL completed, NSError *error) that will
 *      receive a YES or NO BOOL indicating the completion state and/or an NSError object if there
 *      is a failure.
 */
+ (void)startWithDefaultConfiguration:(BOOL)shouldUseDefault completion:(MASCompletionErrorBlock _Nullable)completion;



/**
 *  Starts the lifecycle of the MAS processes with given JSON configuration data.
 *  This method will overwrite JSON configuration (if they are different) that was stored in keychain.
 *
 *  Although an asynchronous block callback parameter is provided for response usage,
 *  optionally you can set that to nil and the caller can observe the lifecycle
 *
 *  The MAS lifecycle notifications are:
 *
 *      MASWillStartNotification
 *      MASDidFailToStartNotification
 *      MASDidStartNotification
 *
 *  The application registration notifications are:
 *
 *      MASApplicationWillRegisterNotification
 *      MASApplicationDidFailToRegisterNotification
 *      MASApplicationDidRegisterNotification
 *
 *  @param json       NSDictionary of JSON configuration object.
 *  @param completion An MASCompletionErrorBlock type (BOOL completed, NSError *error) that will
 *      receive a YES or NO BOOL indicating the completion state and/or an NSError object if there
 *      is a failure.
 */
+ (void)startWithJSON:(NSDictionary *_Nonnull)jsonConfiguration completion:(MASCompletionErrorBlock _Nullable)completion;



/**
 *  Starts the lifecycle of the MAS processes with given JSON configuration file path, enrolment URL or nil.
 *  This method will overwrite JSON configuration (if they are different) that was stored in keychain when configuration file path or enrolment URL is provided.
 *  When URL is recognized as nil, this method will initialize SDK by using last used JSON configuration that is stored in keychain storage,
 *  or load JSON configuration from defined default configuration file name.
 *
 *  Enrolment URL is an URL from gateway containing some of credentials required to establish secure connection. 
 *  The gateway must be configured to generate and handle enrolment process with client side SDK.
 *  The enrolment URL can be retrieved in many ways which has to be configured properly along with the gateway in regards of the enrolment process.
 *  MASFoundation SDK does not request, or retrieve the enrolment URL by itself.
 *
 *  Although an asynchronous block callback parameter is provided for response usage,
 *  optionally you can set that to nil and the caller can observe the lifecycle
 *
 *  The MAS lifecycle notifications are:
 *
 *      MASWillStartNotification
 *      MASDidFailToStartNotification
 *      MASDidStartNotification
 *
 *  The application registration notifications are:
 *
 *      MASApplicationWillRegisterNotification
 *      MASApplicationDidFailToRegisterNotification
 *      MASApplicationDidRegisterNotification
 *
 *  @param url       NSURL of JSON configuration file path or enrolment URL.
 *  @param completion An MASCompletionErrorBlock type (BOOL completed, NSError *error) that will
 *      receive a YES or NO BOOL indicating the completion state and/or an NSError object if there
 *      is a failure.
 */
+ (void)startWithURL:(NSURL *_Nullable)url completion:(MASCompletionErrorBlock _Nullable)completion;



/**
 *  Stops the lifecycle of all MAS processes.
 *
 *  Although an asynchronous block callback parameter is provided for response usage, 
 *  optionally you can set that to nil and the caller can observe the lifecycle 
 *  notifications instead.
 *
 *  The lifecycle notifications are:
 *
 *      MASWillStopNotification
 *      MASDidFailToStopNotification
 *      MASDidStopNotification
 *
 *  @param completion An MASCompletionErrorBlock type (BOOL completed, NSError *error) that will
 *      receive a YES or NO BOOL indicating the completion state and/or an NSError object if there
 *      is a failure.
 */
+ (void)stop:(MASCompletionErrorBlock _Nullable)completion;



///--------------------------------------
/// @name Gateway Monitoring
///--------------------------------------

# pragma mark - Gateway Monitoring

/**
 *  Retrieves a simple boolean indicator if the gateway is currently reachable or not.
 *
 *  @return Returns YES if it is reachable, NO if not.
 */
+ (BOOL)gatewayIsReachable;



/**
 *  Retrieves the current gateway monitoring status of the Gateway connection.
 *
 *  The monitoring status enumerated values to their string equivalents are:
 *
 *      MASGatewayMonitoringStatusNotReachable = "Not Reachable"
 *      MASGatewayMonitoringStatusReachableViaWWAN = "Reachable Via WWAN"
 *      MASGatewayMonitoringStatusReachableViaWiFi = "Reachable Via WiFi"
 *
 *  @return Returns the gateway monitoring status as a human readable NSString.
 */
+ (NSString *_Nonnull)gatewayMonitoringStatusAsString;



///--------------------------------------
/// @name HTTP Requests
///--------------------------------------

# pragma mark - HTTP Requests

/**
 *  Request method for an HTTP DELETE call from the Gateway.  This type of HTTP Method type
 *  places it's parameters within the NSURL itself as an HTTP query extension as so:
 *
 *      https://<hostname>:<port>/<endPointPath><?type=value&type2=value2&...>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  This version defaults the request/response content type encoding to JSON.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)deleteFrom:(NSString *_Nonnull)endPointPath
    withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
        andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
        completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP DELETE call from the Gateway.  This type of HTTP Method type
 *  places it's parameters within the NSURL itself as an HTTP query extension as so:
 *
 *      https://<hostname>:<port>/<endPointPath><?type=value&type2=value2&...>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)deleteFrom:(NSString *_Nonnull)endPointPath
    withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
        andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
      requestType:(MASRequestResponseType)requestType
      responseType:(MASRequestResponseType)responseType
        completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP DELETE call from the Gateway.  This type of HTTP Method type
 *  places it's parameters within the NSURL itself as an HTTP query extension as so:
 *
 *      https://<hostname>:<port>/<endPointPath><?type=value&type2=value2&...>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param isPublic Boolean value whether the request is being made outside of primary gateway.
 *      When the value is set to true, all automatically injected credentials in SDK will be excluded in the request.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)deleteFrom:(NSString *_Nonnull)endPointPath
    withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
        andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
       requestType:(MASRequestResponseType)requestType
      responseType:(MASRequestResponseType)responseType
          isPublic:(BOOL)isPublic
        completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP GET call from the Gateway.  This type of HTTP Method type
 *  places it's parameters within the NSURL itself as an HTTP query extension as so:
 *
 *      https://<hostname>:<port>/<endPointPath><?type=value&type2=value2&...>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  This version defaults the request/response content type encoding to JSON.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)getFrom:(NSString *_Nonnull)endPointPath
 withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
     andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
     completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP GET call from the Gateway.  This type of HTTP Method type
 *  places it's parameters within the NSURL itself as an HTTP query extension as so:
 *
 *      https://<hostname>:<port>/<endPointPath><?type=value&type2=value2&...>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)getFrom:(NSString *_Nonnull)endPointPath
 withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
     andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
    requestType:(MASRequestResponseType)requestType
   responseType:(MASRequestResponseType)responseType
     completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP GET call from the Gateway.  This type of HTTP Method type
 *  places it's parameters within the NSURL itself as an HTTP query extension as so:
 *
 *      https://<hostname>:<port>/<endPointPath><?type=value&type2=value2&...>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param isPublic Boolean value whether the request is being made outside of primary gateway.
 *      When the value is set to true, all automatically injected credentials in SDK will be excluded in the request.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)getFrom:(NSString *_Nonnull)endPointPath
 withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
     andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
    requestType:(MASRequestResponseType)requestType
   responseType:(MASRequestResponseType)responseType
       isPublic:(BOOL)isPublic
     completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP PATCH call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  This version defaults the request/response content type encoding to JSON.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)patchTo:(NSString *_Nonnull)endPointPath
 withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
     andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
     completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP PATCH call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)patchTo:(NSString *_Nonnull)endPointPath
 withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
     andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
    requestType:(MASRequestResponseType)requestType
   responseType:(MASRequestResponseType)responseType
     completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP PATCH call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param isPublic Boolean value whether the request is being made outside of primary gateway.
 *      When the value is set to true, all automatically injected credentials in SDK will be excluded in the request.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)patchTo:(NSString *_Nonnull)endPointPath
 withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
     andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
    requestType:(MASRequestResponseType)requestType
   responseType:(MASRequestResponseType)responseType
       isPublic:(BOOL)isPublic
     completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP POST call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  This version defaults the request/response content type encoding to JSON.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerinfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)postTo:(NSString *_Nonnull)endPointPath
withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
    andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
    completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP POST call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerinfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)postTo:(NSString *_Nonnull)endPointPath
withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
    andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
   requestType:(MASRequestResponseType)requestType
  responseType:(MASRequestResponseType)responseType
    completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP POST call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerinfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param isPublic Boolean value whether the request is being made outside of primary gateway.
 *      When the value is set to true, all automatically injected credentials in SDK will be excluded in the request.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)postTo:(NSString *_Nonnull)endPointPath
withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
    andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
   requestType:(MASRequestResponseType)requestType
  responseType:(MASRequestResponseType)responseType
      isPublic:(BOOL)isPublic
    completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP PUT call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  This version defaults the request/response content type encoding to JSON.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)putTo:(NSString *_Nonnull)endPointPath
withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
   andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
   completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP PUT call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)putTo:(NSString *_Nonnull)endPointPath
withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
   andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
  requestType:(MASRequestResponseType)requestType
 responseType:(MASRequestResponseType)responseType
   completion:(MASResponseInfoErrorBlock _Nullable)completion;



/**
 *  Request method for an HTTP PUT call to the Gateway.  This type of HTTP Method type
 *  places it's parameters within the HTTP body in www-form-url-encoded format:
 *
 *      <body>
 *          <type=value&type2=value2&...>
 *      </body>
 *
 *  If endPointPath is full URL format (including port number and http protocol), SDK will validate the server from the client side through SSL pinning (authentication challenge) with
 *  provided subjectKeyHash (also known as public key hash) in configuration in mag.mobile_sdk.trusted_cert_pinned_public_key_hashes and mag.mobile_sdk.enable_public_key_pinning.
 *  ALL of servers' public key hashes in certificate chain must be defined in the list.  This means when it is configured to use public key hash pinning for SSL pinning,
 *  subjectKeyHash (public key hash) of the gateway must be also present within the list.  The list can contain multiple hash values in array for multiple servers.
 *
 *  When SDK fails to validate SSL with certificate or subjectKeyHash pinning for communication to HTTPs, SDK will cancel the request.
 *
 *  If endPointPath is full URL format, upon successful SSL pinning validation, SDK will also validate the user session against primary gateway regardless the request is being made
 *  to the primary gateway or not.  To ensure bypass the user session validation for public API, use [MAS deleteFrom:withParameters:requestType:responseType:isPublic:completion:] method
 *  with isPublic being YES.
 *
 *  @param endPointPath The specific end point path fragment NSString to append to the base
 *      Gateway URL.  endPointPath value can also be defined as full URL format; in this case, SDK must be configured to perform SSL pinning with public key hashes
 *      which can be configured in JSON configuration.
 *  @param parameterInfo An NSDictionary of key/value parameter values that will go into the
 *      query portion of the URL.
 *  @param headerInfo An NSDictionary of key/value header values that will go into the HTTP
 *      header.
 *  @param requestType The mime type content encoding expected for the parameter encoding.
 *  @param responseType The mime type expected in the body of the response.
 *  @param isPublic Boolean value whether the request is being made outside of primary gateway.
 *      When the value is set to true, all automatically injected credentials in SDK will be excluded in the request.
 *  @param completion An MASResponseInfoErrorBlock (NSDictionary *responseInfo, NSError *error) that will
 *      receive the JSON response object or an NSError object if there is a failure.
 */
+ (void)putTo:(NSString *_Nonnull)endPointPath
withParameters:(NSDictionary<NSString *, NSString *> *_Nullable)parameterInfo
   andHeaders:(NSDictionary<NSString *, NSString *> *_Nullable)headerInfo
  requestType:(MASRequestResponseType)requestType
 responseType:(MASRequestResponseType)responseType
     isPublic:(BOOL)isPublic
   completion:(MASResponseInfoErrorBlock _Nullable)completion;


///--------------------------------------
/// @name JWT Signing
///--------------------------------------

# pragma mark - JWT Signing



/**
 Signs MASClaims object with default private key from device registration against primary gateway.
 Some of read-write claims, such as exp, content, and/or contentType, should properly be prepared.

 @param claims MASClaims object containing claims for JWT
 @param error NSERror error reference object that returns any error occurred during JWT construction.
 @return NSString of JWT token.
 */
+ (NSString * _Nullable)signWithClaims:(MASClaims *_Nonnull)claims error:(NSError *__nullable __autoreleasing *__nullable)error;




/**
 Signs MASClaims object with custom private key in NSData format. Private key should be in NSData format and should have been signed using RS256 algorithm.
 Some of read-write claims, such as exp, content, and/or contentType, should properly be prepared.
 
 @param claims MASClaims object containing claims for JWT
 @param privateKey Custom private key in NSData format signed using RS256 algorithm.
 @param error NSERror error reference object that returns any error occurred during JWT construction.
 @return NSString of JWT token.
 */
+ (NSString * _Nullable)signWithClaims:(MASClaims *_Nonnull)claims privateKey:(NSData *_Nonnull)privateKey error:(NSError *__nullable __autoreleasing *__nullable)error;


#ifdef DEBUG

///--------------------------------------
/// @name Debug Only
///--------------------------------------

# pragma mark - Debug only

/**
 *  Method for debug purposes to view the current runtime contents of the framework on the
 *  debug console.  The debugDescription results of the MASNetworkingService, MASApplication,
 *  MASDevice and MASUser are shown if available.
 *
 *  This will not be compiled into release versions of an application.
 */
+ (void)currentStatusToConsole;

#endif

@end
