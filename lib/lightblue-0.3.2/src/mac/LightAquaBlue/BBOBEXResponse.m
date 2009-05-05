/*
 * Copyright (c) 2006 Bea Lam. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//
//  BBOBEXResponse.m
//  LightAquaBlue
//

#import "BBOBEXResponse.h"
#import "BBOBEXHeaderSet.h"

@implementation BBOBEXResponse

+ (id)responseWithCode:(int)responseCode
               headers:(BBOBEXHeaderSet *)headers
{
    return [[[BBOBEXResponse alloc] initWithCode:responseCode
                                         headers:headers] autorelease];
}

- (id)initWithCode:(int)responseCode
           headers:(BBOBEXHeaderSet *)headers
{
    self = [super init];
    
    mCode = responseCode;
    mHeaders = [headers retain];
    
    return self;
}

- (int)responseCode
{
    return mCode;
}

- (NSString *)responseCodeDescription
{
    switch (mCode) {
        case kOBEXResponseCodeContinueWithFinalBit:
            return @"Continue";
        case kOBEXResponseCodeSuccessWithFinalBit:
            return @"Success"; 
        case kOBEXResponseCodeCreatedWithFinalBit:
            return @"Created"; 
        case kOBEXResponseCodeAcceptedWithFinalBit:
            return @"Accepted";
        case kOBEXResponseCodeNonAuthoritativeInfoWithFinalBit:
            return @"Non-authoritative info";           
        case kOBEXResponseCodeNoContentWithFinalBit:
            return @"No content";           
        case kOBEXResponseCodeResetContentWithFinalBit:
            return @"Reset content";        
        case kOBEXResponseCodePartialContentWithFinalBit:
            return @"Partial content";      
        case kOBEXResponseCodeMultipleChoicesWithFinalBit:
            return @"Multiple choices";     
        case kOBEXResponseCodeMovedPermanentlyWithFinalBit:
            return @"Moved permanently";    
        case kOBEXResponseCodeMovedTemporarilyWithFinalBit:
            return @"Moved temporarily";    
        case kOBEXResponseCodeSeeOtherWithFinalBit:
            return @"See other";            
        case kOBEXResponseCodeNotModifiedWithFinalBit:
            return @"Code not modified";    
        case kOBEXResponseCodeUseProxyWithFinalBit:
            return @"Use proxy";            
        case kOBEXResponseCodeBadRequestWithFinalBit:
            return @"Bad request";          
        case kOBEXResponseCodeUnauthorizedWithFinalBit:
            return @"Unauthorized";         
        case kOBEXResponseCodePaymentRequiredWithFinalBit:
            return @"Payment required";     
        case kOBEXResponseCodeForbiddenWithFinalBit:
            return @"Forbidden";            
        case kOBEXResponseCodeNotFoundWithFinalBit:
            return @"Not found";            
        case kOBEXResponseCodeMethodNotAllowedWithFinalBit:
            return @"Method not allowed";   
        case kOBEXResponseCodeNotAcceptableWithFinalBit:
            return @"Not acceptable";       
        case kOBEXResponseCodeProxyAuthenticationRequiredWithFinalBit:
            return @"Proxy authentication required";            
        case kOBEXResponseCodeRequestTimeOutWithFinalBit:
            return @"Request time out";         
        case kOBEXResponseCodeConflictWithFinalBit:
            return @"Conflict";         
        case kOBEXResponseCodeGoneWithFinalBit:
            return @"Gone";         
        case kOBEXResponseCodeLengthRequiredFinalBit:
            return @"Length required";          
        case kOBEXResponseCodePreconditionFailedWithFinalBit:
            return @"Precondition failed";      
        case kOBEXResponseCodeRequestedEntityTooLargeWithFinalBit:
            return @"Requested entity too large";           
        case kOBEXResponseCodeRequestURLTooLargeWithFinalBit:
            return @"Requested URL too large";          
        case kOBEXResponseCodeUnsupportedMediaTypeWithFinalBit:
            return @"Unsupported media type";           
        case kOBEXResponseCodeInternalServerErrorWithFinalBit:
            return @"Internal server error";            
        case kOBEXResponseCodeNotImplementedWithFinalBit:
            return @"Not implemented";          
        case kOBEXResponseCodeBadGatewayWithFinalBit:
            return @"Bad gateway";          
        case kOBEXResponseCodeServiceUnavailableWithFinalBit:
            return @"Service unavailable";  
        case kOBEXResponseCodeGatewayTimeoutWithFinalBit:
            return @"Gateway timeout";      
        case kOBEXResponseCodeHTTPVersionNotSupportedWithFinalBit:
            return @"HTTP version not supported";           
        case kOBEXResponseCodeDatabaseFullWithFinalBit:
            return @"Database full";            
        case kOBEXResponseCodeDatabaseLockedWithFinalBit:
            return @"Database locked";
        default:
            return @"Unknown response";
    }
}

- (BBOBEXHeaderSet *)allHeaders
{
    return mHeaders;
}

- (void)dealloc
{
    [mHeaders release];
    [super dealloc];
}

@end
