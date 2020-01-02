/*
 *  Bean Java VM
 *  Copyright (C) 2005-2015 Christian Lins <christian@lins.me>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

package java.lang;

import java.nio.charset.Charset;

/**
 *
 * @author Christian Lins
 */
public class String {
    
    public String() {
    }
    
    public byte[] getBytes() {
        return getBytes(Charset.defaultCharset());
    }
    
    // FIXME
    public byte[] getBytes(Charset cset) {
        byte[] buf = new byte[3];
        buf[0] = 65;
        buf[1] = 66;
        buf[2] = 67;
        return buf;
    }
}
