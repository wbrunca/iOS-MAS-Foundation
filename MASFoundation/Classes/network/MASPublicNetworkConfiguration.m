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

#import "MASNetworkingService.h"

@interface MASPublicNetworkConfiguration ()

@property (nonatomic, assign) MASSessionAuthenticationChallengeBlock sessionAuthChallengeBlock;

@property (nonatomic, assign) MASTaskAuthenticationChallengeBlock taskAuthChallengeBlock;

@end

@implementation MASPublicNetworkConfiguration


///--------------------------------------
/// @name Life Cycle
///--------------------------------------

# pragma mark - Life Cycle

- (id)init
{
    @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                   reason:@"Cannot call base init, call designated factory method" userInfo:nil];
    
    return nil;
}


+ (instancetype)sharedConfiguration
{
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^
                  {
                      sharedInstance = [[MASPublicNetworkConfiguration alloc] initProtected];
                  });
    
    return sharedInstance;
}


- (instancetype)initProtected
{
    self = [super init];
    
    if (!self)
    {
        return nil;
    }
    
    return self;
}


///--------------------------------------
/// @name Authentication Challenge Blocks
///--------------------------------------

# pragma mark - Authentication Challenge Blocks

- (void)setSessionDidReceiveAuthenticationChallengeBlock:(MASSessionAuthenticationChallengeBlock)authChallengeBlock
{
    _sessionAuthChallengeBlock = authChallengeBlock;
}


- (MASSessionAuthenticationChallengeBlock)sessionDidReceiveAuthenticationChallengeBlock
{
    return _sessionAuthChallengeBlock;
}


- (void)setTaskDidReceiveAuthenticationChallengeBlock:(MASTaskAuthenticationChallengeBlock)authChallengeBlock
{
    _taskAuthChallengeBlock = authChallengeBlock;
}


- (MASTaskAuthenticationChallengeBlock)taskDidReceiveAuthenticationChallengeBlock
{
    return _taskAuthChallengeBlock;
}


///--------------------------------------
/// @name Configuration
///--------------------------------------

# pragma mark - Configuration

- (void)updateConfiguration
{
    [[MASNetworkingService sharedService] establishPublicURLSession];
}

@end
