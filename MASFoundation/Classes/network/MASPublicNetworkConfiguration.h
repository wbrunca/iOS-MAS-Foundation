//
//  MASPublicNetworkConfiguration.h
//  MASFoundation
//
//  Copyright (c) 2016 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

@import Foundation;

#import "MASConstants.h"

/**
 MASPublicNetworkConfiguration is the class where all network security policy is configured for public network (i.e. any other request being made other than primary gateway in the configuration).  Configuration values are set upon SDK initialization or upon [[MASPublicNetworkConfiguration sharedConfiguration] updateConfiguration].
 MASPublicNetworkConfiguration is a singleton object; base init cannot be called and initialize the object.
 */
@interface MASPublicNetworkConfiguration : NSObject


///--------------------------------------
/// @name Properties
///--------------------------------------

# pragma mark - Properties

/**
 SSL Pinning mode for which server trust should be evaluated against the pinned SSL certificates.  Defaults to `MASSSLPinningModeNone`.
 */
@property (assign) MASSSLPinningMode pinningMode;


/**
 Whether to allow invalid or expired SSL certificates or not.  Defaults to `NO`.
 */
@property (nonatomic, assign) BOOL allowInvalidCertificates;


/**
 Whether to evaluate entire certificate chain or not.  Defaults to `YES`.
 */
@property (nonatomic, assign) BOOL validatesCertficateChain;


/**
 An array of certificates to be used to evaluate server trust based on SSL pinning mode.
 */
@property (nonatomic, strong) NSArray *pinnedCertificates;


///--------------------------------------
/// @name Life Cycle
///--------------------------------------

# pragma mark - Life Cycle

/**
 Shared instance of the configuration object.

 @return MASPublicNetworkConfiguration singleton object.
 */
+ (instancetype)sharedConfiguration;



///--------------------------------------
/// @name Authentication Challenge Blocks
///--------------------------------------

# pragma mark - Authentication Challenge Blocks

/**
 Sets a block of code to be executed when a connection level authentication challenge is received.

 @param authChallengeBlock A block object to be executed when a connection level authentication challenge is received.
 */
- (void)setSessionDidReceiveAuthenticationChallengeBlock:(MASSessionAuthenticationChallengeBlock)authChallengeBlock;



/**
 Returns a block object that will be executed when a connection level authentication challegne is received.

 @return MASSessionAuthenticationChallengeBlock authentication challenge block.
 */
- (MASSessionAuthenticationChallengeBlock)sessionDidReceiveAuthenticationChallengeBlock;



/**
 Sets a block of code to be executed when a session task level authentication challenge is received.

 @param authChallengeBlock A block object to be executed when a session task level authentication challenge is received.
 */
- (void)setTaskDidReceiveAuthenticationChallengeBlock:(MASTaskAuthenticationChallengeBlock)authChallengeBlock;



/**
 Returns a block object that will be executed when a session task level authentication challenge is received.

 @return MASTaskAuthenticationChallengeBlock authentication challenge block.
 */
- (MASTaskAuthenticationChallengeBlock)taskDidReceiveAuthenticationChallengeBlock;



///--------------------------------------
/// @name Configuration
///--------------------------------------

# pragma mark - Configuration

/**
 A method to re-configure all network security policy based on the current values.  Security policy values are only being set upon SDK initialization; therefore, if any change is needed after SDK initialization, make sure to call updateConfiguration method to reflect all changes.
 */
- (void)updateConfiguration;

@end
