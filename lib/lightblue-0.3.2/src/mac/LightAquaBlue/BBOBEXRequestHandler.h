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
//  BBOBEXRequestHandler.h
//  LightAquaBlue
//
//  These are internal classes used by BBBluetoothOBEXServer for handling
//  incoming client requests. Each BBOBEXRequestHandler subclass encapsulates 
//  the process for handling a particular type of request.
//

#import <Foundation/Foundation.h>
#import <IOBluetooth/OBEX.h>

@class BBBluetoothOBEXServer;
@class BBOBEXHeaderSet;
@class BBMutableOBEXHeaderSet;
@class OBEXSession;


@interface BBOBEXRequestHandler : NSObject {
    BBBluetoothOBEXServer *mServer;
    SEL mServerEventSelector;
    OBEXSession *mSession;
    
    int mNextResponseCode;
    BBMutableOBEXHeaderSet *mNextResponseHeaders;
}

+ (void)setDebug:(BOOL)debug;

- (id)initWithServer:(BBBluetoothOBEXServer *)server 
       eventSelector:(SEL)selector
             session:(OBEXSession *)session;

- (void)setNextResponseCode:(int)responseCode;

- (void)addResponseHeaders:(BBOBEXHeaderSet *)responseHeaders;

- (BOOL)handleRequestEvent:(const OBEXSessionEvent *)event;


/*** for subclasses - calls errorOccurred:description: on delegate ***/
- (void)errorOccurred:(OBEXError)error 
          description:(NSString *)description;


/*** methods below must be overriden by subclasses, and should be regarded 
    as 'protected' - they don't need to be called by outside classes ***/

- (BOOL)readOBEXRequestHeaders:(BBMutableOBEXHeaderSet **)requestHeaders
               andRequestFlags:(OBEXFlags *)flags
              fromSessionEvent:(const OBEXSessionEvent *)event; 

- (void)prepareResponseForRequestWithHeaders:(BBMutableOBEXHeaderSet *)requestHeaders
                                       flags:(OBEXFlags)flags
                        isFinalRequestPacket:(BOOL)isFinalRequestPacket;

- (OBEXError)sendNextResponsePacket;

- (void)handleRequestAborted;

- (void)notifyRequestFinished;

@end


@interface BBOBEXConnectRequestHandler : BBOBEXRequestHandler {
    CFMutableDataRef mHeadersDataRef;
    OBEXMaxPacketLength mMaxPacketLength;
}
@end

@interface BBOBEXDisconnectRequestHandler : BBOBEXRequestHandler {
    CFMutableDataRef mHeadersDataRef;
}
@end

@interface BBOBEXPutRequestHandler : BBOBEXRequestHandler {
    CFMutableDataRef mHeadersDataRef;    
    BBMutableOBEXHeaderSet *mPreviousRequestHeaders;
    NSOutputStream *mOutputStream;
    BOOL mDefinitelyIsPut;
    BOOL mAborted;
}
@end

@interface BBOBEXGetRequestHandler : BBOBEXRequestHandler {
    CFMutableDataRef mHeadersDataRef;    
    NSMutableData *mSentBodyData;
    NSInputStream *mInputStream;
    BOOL mAborted;    
}
@end

@interface BBOBEXSetPathRequestHandler : BBOBEXRequestHandler {
    CFMutableDataRef mHeadersDataRef;    
}
@end
