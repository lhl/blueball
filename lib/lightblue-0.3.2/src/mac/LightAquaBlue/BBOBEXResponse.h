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
//  BBOBEXResponse.h
//  LightAquaBlue
//
//  Contains the details for an OBEX server response. 
//
//  This is used by BBBluetoothOBEXClient to pass the details of an OBEX
//  server response to its delegate.
//

#import <Cocoa/Cocoa.h>

@class BBOBEXHeaderSet;

@interface BBOBEXResponse : NSObject {
    int mCode;
    BBOBEXHeaderSet *mHeaders;
}

+ (id)responseWithCode:(int)responseCode
               headers:(BBOBEXHeaderSet *)headers;

- (id)initWithCode:(int)responseCode
           headers:(BBOBEXHeaderSet *)headers;

/*
 * Returns the response code.
 *
 * Use the response codes listed in the OBEXOpCodeResponseValues enum in
 * <IOBluetooth/OBEX.h> to match against this response code. If the client
 * request was accepted by the OBEX server, this response code will be 
 * kOBEXResponseCodeSuccessWithFinalBit. Otherwise, it will be set to one of
 * the other response codes that end with "WithFinalBit".
 */
- (int)responseCode;

/*
 * Returns a string description of the response code. E.g. 
 * kOBEXResponseCodeSuccessWithFinalBit translates to "Success".
 */
- (NSString *)responseCodeDescription;

/*
 * Returns the response headers.
 */
- (BBOBEXHeaderSet *)allHeaders;

@end
