//
//  MASPublicNetworkConfiguration.h
//  MASFoundation
//
//  Copyright (c) 2016 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//


#import <Foundation/Foundation.h>

/**
 *  The enumerated MASSSLPinningMode that indicates which method to be used for SSL pinning on network requests other than currently active gateway.
 */
typedef NS_ENUM(NSInteger, MASSSLPinningMode) {
    MASSSLPinningModeNone,
    MASSSLPinningModePublicKey,
    MASSSLPinningModeCertificate
};

typedef NSURLSessionAuthChallengeDisposition (^MASSessionAuthenticationChallengeBlock)(NSURLSession *session, NSURLAuthenticationChallenge *challenge, NSURLCredential *credential);

typedef NSURLSessionAuthChallengeDisposition (^MASTaskAuthenticationChallengeBlock)(NSURLSession *session, NSURLSessionTask *task, NSURLAuthenticationChallenge *challenge, NSURLCredential *credential);


@interface MASPublicNetworkConfiguration : NSObject

@property (nonatomic, assign) MASSSLPinningMode pinningMode;

@property (nonatomic, assign) BOOL allowInvalidCertificates;

@property (nonatomic, assign) BOOL validatesCertficateChain;

@property (nonatomic, strong) NSArray *pinnedCertificates;

+ (instancetype)sharedConfiguration;

- (void)setSessionDidReceiveAuthenticationChallengeBlock:(MASSessionAuthenticationChallengeBlock)authChallengeBlock;

- (void)setTaskDidReceiveAuthenticationChallengeBlock:(MASTaskAuthenticationChallengeBlock)authChallengeBlock;

@end
