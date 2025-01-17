//
//  NSURL+MASPrivate.m
//  MASFoundation
//
//  Copyright (c) 2017 CA. All rights reserved.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

#import "NSURL+MASPrivate.h"

#import "MASConfiguration.h"


@implementation NSURL (MASPrivate)


- (BOOL)isProtectedEndpoint:(NSString *)thisEndpoint
{
    NSURL *isThisURL = [NSURL URLWithString:thisEndpoint];
    NSURL *thisURL = nil;
    
    if (isThisURL && isThisURL.scheme && isThisURL.host)
    {
        thisURL = [NSURL URLWithString:thisEndpoint];
    }
    else {
        NSString *endPoint = [NSString stringWithFormat:@"%@%@",[MASConfiguration currentConfiguration].gatewayPrefix, thisEndpoint];
        thisURL = [NSURL URLWithString:endPoint relativeToURL:[MASConfiguration currentConfiguration].gatewayUrl];
    }
    
    return [thisURL.absoluteString hasPrefix:self.absoluteString];
}


- (NSDictionary *)extractQueryParameters
{
    NSMutableDictionary *queryStringDictionary = [[NSMutableDictionary alloc] init];
    NSArray *urlComponentsSeperatedwithQuestionMark = [[self description] componentsSeparatedByString:@"?"];
    NSArray *urlComponents = [urlComponentsSeperatedwithQuestionMark[1] componentsSeparatedByString:@"&"];
    
    for (NSString *keyValuePair in urlComponents)
    {
        NSArray *pairComponents = [keyValuePair componentsSeparatedByString:@"="];
        NSString *key = [pairComponents objectAtIndex:0];
        NSString *value = [pairComponents objectAtIndex:1];
        
        [queryStringDictionary setObject:value forKey:key];
    }
    
    return queryStringDictionary;
}

@end
