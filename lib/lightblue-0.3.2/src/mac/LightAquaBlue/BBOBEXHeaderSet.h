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
//  BBOBEXHeaderSet.h
//  LightAquaBlue
//
//  A collection of unique OBEX headers. 
// 
//  The mutable counterpart to this class is BBMutableOBEXHeaderSet.
//

#import <Cocoa/Cocoa.h>
#import <CoreFoundation/CoreFoundation.h>

#import <IOBluetooth/OBEX.h>

@interface BBOBEXHeaderSet : NSObject {
    NSMutableDictionary *mDict;
    NSMutableArray *mKeys;
}

/*
 * Creates and returns an empty header set.
 */
+ (id)headerSet;

/*
 * Returns whether this header set contains the header with <headerID>.
 * 
 * Common header IDs are defined in the OBEXHeaderIdentifiers enum in
 * <IOBluetooth/OBEX.h> (for example, kOBEXHeaderIDName).
 */
- (BOOL)containsValueForHeader:(uint8_t)headerID;

/*
 * Returns the number of headers in this header set.
 */
- (unsigned)count;

/*
 * Returns the "Count" header value, or 0 if the header is not present or cannot
 * be read.
 */
- (unsigned int)valueForCountHeader;

/*
 * Returns the value for the Name header, or nil if the header is not present or 
 * cannot be read.
 */
- (NSString *)valueForNameHeader;

/*
 * Returns the value for the Type header, or nil if the header is not present or 
 * cannot be read.
 */
- (NSString *)valueForTypeHeader;

/*
 * Returns the value for the Length header, or 0 if the header is not present or
 * cannot be read.
 */
- (unsigned int)valueForLengthHeader;

/*
 * Returns the value for the 0x44 Time header, or the 0xC4 value if the 0x44 
 * header is not present, or nil if neither header is present or cannot be read.
 */
- (NSDate *)valueForTimeHeader;

/*
 * Returns the value for the Description header, or nil if the header is not
 * present or cannot be read.
 */
- (NSString *)valueForDescriptionHeader;

/*
 * Returns the value for the Target header, or nil if the header is not present
 * or cannot be read.
 */
- (NSData *)valueForTargetHeader;

/*
 * Returns the value for the HTTP header, or nil if the header is not present
 * or cannot be read.
 */
- (NSData *)valueForHTTPHeader;

/*
 * Returns the value for the Who header, or nil if the header is not present
 * or cannot be read.
 */
- (NSData *)valueForWhoHeader;

/*
 * Returns the value for the Connection Id header, or 0 if the header is not
 * present or cannot be read.
 */
- (uint32_t)valueForConnectionIDHeader;

/*
 * Returns the value for the Application Parameters header, or nil if the 
 * header is not present or cannot be read.
 */
- (NSData *)valueForApplicationParametersHeader;

/*
 * Returns the value for the Authorization Challenge header, or nil if the 
 * header is not present or cannot be read.
 */
- (NSData *)valueForAuthorizationChallengeHeader;

/*
 * Returns the value for the Authorization Response header, or nil if the 
 * header is not present or cannot be read.
 */
- (NSData *)valueForAuthorizationResponseHeader;

/*
 * Returns the value for the Object Class header, or nil if the 
 * header is not present or cannot be read.
 */
- (NSData *)valueForObjectClassHeader;

/*
 * Returns the value for the 4-byte header <headerID>, or 0 if the header is 
 * not present or cannot be read as a 4-byte value.
 */
- (unsigned int)valueFor4ByteHeader:(uint8_t)headerID;

/*
 * Returns the value for the byte-sequence header <headerID>, or nil if the
 * header is not present or cannot be read as a byte-sequence value.
 */
 - (NSData *)valueForByteSequenceHeader:(uint8_t)headerID;

/*
 * Returns the value for the 1-byte header <headerID>, or 0 if the header is 
 * not present or cannot be read as a 1-byte value.
 */
- (uint8_t)valueFor1ByteHeader:(uint8_t)headerID;

/*
 * Returns the value for the unicode header <headerID>, or nil if the
 * header is not present or cannot be read as a unicode value.
 */
- (NSString *)valueForUnicodeHeader:(uint8_t)headerID;

/*
 * Returns all the headers in the header set as a list of NSNumber objects.
 * Each NSNumber contains an unsigned char value (the header ID).
 *
 * The headers are returned in the order in which they were added.
 */
- (NSArray *)allHeaders;

/*
 * Returns a stream of bytes that contain the headers in this header set, as
 * specified by the IrOBEX specification (section 2.1).
 */
- (NSMutableData *)toBytes;

@end
