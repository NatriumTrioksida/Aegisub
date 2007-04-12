// Copyright (c) 2007, Rodrigo Braz Monteiro
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the Aegisub Group nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// -----------------------------------------------------------------------------
//
// AEGISUB
//
// Website: http://aegisub.cellosoft.com
// Contact: mailto:zeratul@cellosoft.com
//


///////////
// Headers
#include "gl_text.h"


///////////////////
// Static instance
OpenGLText* OpenGLText::instance;


///////////////
// Constructor
OpenGLText::OpenGLText() {
	r = g = b = a = 1.0f;
}


//////////////
// Destructor
OpenGLText::~OpenGLText() {
}


////////////////
// Get instance
OpenGLText* OpenGLText::GetInstance() {
	if (!instance) instance = new OpenGLText();
	wxASSERT(instance);
	return instance;
}


////////////
// Set font
void OpenGLText::DoSetFont(wxString face,int size) {
}


//////////////
// Set colour
void OpenGLText::DoSetColour(wxColour col,float alpha) {
	r = col.Red() / 255.0f;
	g = col.Green() / 255.0f;
	b = col.Blue() / 255.0f;
	a = alpha;
}


/////////
// Print
void OpenGLText::DoPrint(wxString text,int x,int y) {
}


///////////////
// Get a glyph
OpenGLTextGlyph OpenGLText::GetGlyph(int i) {
	glyphMap::iterator res = glyphs.find(i);

	// Found
	if (res != glyphs.end()) return res->second;

	// Not found, create it
	return CreateGlyph(i);
}


//////////////////
// Create a glyph
OpenGLTextGlyph OpenGLText::CreateGlyph(int n) {
	// Create glyph
	OpenGLTextGlyph glyph;
	glyph.x = 0;
	glyph.y = 0;
	glyph.w = 0;
	glyph.h = 0;
	glyph.tex = 0;

	// Render glyph;
	int w = 16;
	int h = 16;

	// Insert into some texture
	bool ok = false;
	for (unsigned int i=0;i<textures.size();i++) {
		if (textures[i]->CanFit(w,h)) {
			textures[i]->Insert(glyph);
			ok = true;
		}
	}

	// No texture could fit it, create a new one
	if (!ok) {
		textures.push_back(new OpenGLTextTexture());
		textures.back()->Insert(glyph);
	}

	// Set glyph and return it
	glyphs[n] = glyph;
	return glyph;
}


///////////////////////
// Texture constructor
OpenGLTextTexture::OpenGLTextTexture() {
}


//////////////////////
// Texture destructor
OpenGLTextTexture::~OpenGLTextTexture() {
}


//////////////////////////
// Can fit a glyph in it?
bool OpenGLTextTexture::CanFit(int w,int h) {
	return true;
}


////////////////////////
// Insert a glyph in it
void OpenGLTextTexture::Insert(OpenGLTextGlyph glyph) {
}

