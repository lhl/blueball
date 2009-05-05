# Copyright (c) 2006 Bea Lam. All rights reserved.
# 
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

"""
Provides a python interface to the LightAquaBlue Framework classes, through
PyObjC.    
    
See http://pyobjc.sourceforge.net for details on how to access Objective-C 
classes through PyObjC.
"""

_FRAMEWORK_PATH = u'/Library/Frameworks/LightAquaBlue.framework'

import os.path
if not os.path.isdir(_FRAMEWORK_PATH):
    raise ImportError("Cannot load LightAquaBlue framework, not found at" + \
        _FRAMEWORK_PATH)
        
import objc
objc.loadBundle("LightAquaBlue", globals(), 
   bundle_path=objc.pathForFramework(_FRAMEWORK_PATH))
   
   
def _setmethodsignatures():   
    # return int, take (object, object, object, output unsigned char, output int)           
    # i.e. in python: return (int, char, int), take (object, object, object)
    objc.setSignatureForSelector("BBServiceAdvertiser", 
        "addRFCOMMServiceDictionary:withName:UUID:channelID:serviceRecordHandle:",
        "i@0:@@@o^Co^I")
        
    # set to take (6-char array, unsigned char, object)
    # this seems to work even though the selector doesn't take a char aray,
    # it takes a struct 'BluetoothDeviceAddress' which contains a char array.
    objc.setSignatureForSelector("BBBluetoothOBEXClient", 
            "initWithRemoteDeviceAddress:channelID:delegate:", 
            '@@:r^[6C]C@')
   
_setmethodsignatures()   

del objc
