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

package java.io;

/**
 *
 * @author Christian Lins
 */
public class FileOutputStream extends OutputStream {
    
    private boolean useStdOut = false;
            
    public FileOutputStream(FileDescriptor fd) {
        if(FileDescriptor.out.equals(fd)) {
            this.useStdOut = true;
        }
    }

    /** This method is redirected to stdout by Bean JVM */
    private native void writeToStdout(byte[] buf, int off, int len);
    
    public void write(int i) throws IOException {
        if(this.useStdOut) {
            writeToStdout(new byte[] {(byte)(0x000000FF & i)}, 0, 1);
        }
    }
    
    public void write(byte[] buf, int off, int len) throws IOException {
        writeToStdout(buf, off, len);
    }    
}
