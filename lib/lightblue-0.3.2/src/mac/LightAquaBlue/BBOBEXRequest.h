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
//  BBOBEXRequest.h
//  LightAquaBlue
//
//  These are internal classes used by BBBluetoothOBEXClient for sending OBEX 
//  client requests. Each BBOBEXRequest subclass encapsulates the process
//  for performing a particular type of request.
//

#import <Foundation/Foundation.h>
#import <IOBluetooth/OBEX.h>

@class BBBluetoothOBEXClient;
@class BBOBEXHeaderSet;
@class BBMutableOBEXHeaderSet;
@class OBEXSession;

@interface BBOBEXRequest : NSObject
{
    BBBluetoothOBEXClient *mClient;
    SEL mClientEventSelector;
    OBEXSession *mSession;
    BOOL mFinished;
    BBMutableOBEXHeaderSet *mResponseHeaders;
}

+ (void)setDebug:(BOOL)debug;

- (id)initWithClient:(BBBluetoothOBEXClient *)client 
       eventSelector:(SEL)selector
             session:(OBEXSession *)session;

- (BOOL)isFinished;

- (OBEXError)beginWithHeaders:(BBOBEXHeaderSet *)headers;

- (void)receivedResponseWithHeaders:(BBMutableOBEXHeaderSet *)responseHeaders;

- (OBEXError)sendNextRequestPacket;

- (void)finishedWithError:(OBEXError)error responseCode:(int)responseCode;

- (BOOL)readOBEXResponseHeaders:(BBMutableOBEXHeaderSet **)responseHeaders
                andResponseCode:(int *)responseCode
               fromSessionEvent:(const OBEXSessionEvent *)event;
@end

@interface BBOBEXConnectRequest : BBOBEXRequest
{
    CFMutableDataRef mHeadersDataRef;
}
@end

@interface BBOBEXDisconnectRequest : BBOBEXRequest
{
    CFMutableDataRef mHeadersDataRef;    
}
@end

@interface BBOBEXPutRequest : BBOBEXRequest
{
    CFMutableDataRef mHeadersDataRef;
    NSMutableData *mSentBodyData;
    NSInputStream *mInputStream;
}
- (id)initWithClient:(BBBluetoothOBEXClient *)client
       eventSelector:(SEL)selector
             session:(OBEXSession *)session
         inputStream:(NSInputStream *)inputStream;
@end

@interface BBOBEXGetRequest : BBOBEXRequest
{
    CFMutableDataRef mHeadersDataRef;
    NSOutputStream *mOutputStream;
    unsigned int mTotalGetLength;
}
- (id)initWithClient:(BBBluetoothOBEXClient *)client
       eventSelector:(SEL)selector
             session:(OBEXSession *)session
        outputStream:(NSOutputStream *)outputStream;
@end

@interface BBOBEXSetPathRequest : BBOBEXRequest
{
    CFMutableDataRef mHeadersDataRef;
    OBEXFlags mRequestFlags;
}
- (id)initWithClient:(BBBluetoothOBEXClient *)client
       eventSelector:(SEL)selector
             session:(OBEXSession *)session
changeToParentDirectoryFirst:(BOOL)changeToParentDirectoryFirst
createDirectoriesIfNeeded:(BOOL)createDirectoriesIfNeeded;
@end

@interface BBOBEXAbortRequest : BBOBEXRequest
{
    NSStream *mStream;
}
- (id)initWithClient:(BBBluetoothOBEXClient *)client
       eventSelector:(SEL)selector
             session:(OBEXSession *)session
currentRequestStream:(NSStream *)stream;
@end
