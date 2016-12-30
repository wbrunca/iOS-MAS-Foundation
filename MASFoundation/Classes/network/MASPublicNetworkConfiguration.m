//
//  MASPublicNetworkConfiguration.m
//  MASFoundation
//
//  Copyright (c) 2016 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

#import "MASPublicNetworkConfiguration.h"

@implementation MASPublicNetworkConfiguration

+ (instancetype)sharedConfiguration
{
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^
                  {
                      sharedInstance = [[MASPublicNetworkConfiguration alloc] init];
                  });
    
    return sharedInstance;
}

+ (void)setSSLPinningMode:(MASSSLPinningMode)mode
{
    
}

+ (void)setAllowInvalidCertificates:(BOOL)allowInvalidCertificates
{
    
}

+ (void)setValidatesCertificateChain:(BOOL)validatesCertficateChain
{
    
}

+ (void)setPinnedCertificates:(NSArray *)pinnedCertificates
{
    
}

+ (void)setSessionDidReceiveAuthenticationChallengeBlock:(MASSessionAuthenticationChallengeBlock)authChallengeBlock
{
    
}

+ (void)setTaskDidReceiveAuthenticationChallengeBlock:(MASTaskAuthenticationChallengeBlock)authChallengeBlock
{
    
}

@end
