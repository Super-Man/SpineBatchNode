/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software (typically granted by licensing Spine), you
 * may not (a) modify, translate, adapt or otherwise create derivative works,
 * improvements of the Software or develop new applications using the Software
 * or (b) remove, delete, alter or obscure any trademarks or any copyright,
 * trademark, patent or other intellectual property or proprietary rights
 * notices on or in the Software, including any copy thereof. Redistributions
 * in binary or source form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_POLYGONBATCH_H_
#define SPINE_POLYGONBATCH_H_

#include "cocos2d.h"

namespace spine {
    
#define CULLING 0
#define USE_VBO 1

class PolygonBatch : public cocos2d::Ref {
public:
	static PolygonBatch* createWithCapacity (ssize_t capacity);

	void add (const cocos2d::Texture2D* texture,
		const float* vertices, const float* uvs, int verticesCount,
		const int* triangles, int trianglesCount,
		cocos2d::Color4B* color);
	void flush();

#if CULLING
    // for auto culling
    void setVerticesTrianglesCount(int verticesCount, int trianglesCount);
    int getVerticesCount();
    int getTrianglesCount();
#endif
    
    void setupVBOAndVAO();

protected:
	PolygonBatch();
	virtual ~PolygonBatch();
	bool initWithCapacity (ssize_t capacity);
    
    void flushVBO();
    void flushWithoutVBO();

	ssize_t _capacity;
	cocos2d::V2F_C4B_T2F* _vertices;
	int _verticesCount;
	GLushort* _triangles;
	int _trianglesCount;
	const cocos2d::Texture2D* _texture;
    
    GLuint _spineVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices
    
    bool _hasSetupVBOVAO;
};

}

#endif // SPINE_POLYGONBATCH_H_
