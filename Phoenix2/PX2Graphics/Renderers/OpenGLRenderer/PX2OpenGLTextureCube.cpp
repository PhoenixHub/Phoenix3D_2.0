/*
*
* �ļ�����	��	PX2OpenGLTextureCube.cpp
*
*/

#include "PX2OpenGLTextureCube.hpp"
#include "PX2OpenGLMapping.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PdrTextureCube::PdrTextureCube (Renderer*, const TextureCube* texture)
:
mPreviousTexture(0)
{
	mInternalFormat = gOGLTextureInternalFormat[texture->GetFormat()];
	mFormat = gOGLTextureFormat[texture->GetFormat()];
	mType = gOGLTextureType[texture->GetFormat()];
	GLuint usage = gOGLBufferUsage[texture->GetUsage()];

	mNumLevels = texture->GetNumLevels();
	int level;
	for (level = 0; level < mNumLevels; ++level)
	{
		mNumLevelBytes[level] = texture->GetNumLevelBytes(level);
		mDimension[0][level] = texture->GetDimension(0, level);
		mDimension[1][level] = texture->GetDimension(1, level);
	}
	for (/**/; level < Texture::MM_MAX_MIPMAP_LEVELS; ++level)
	{
		mNumLevelBytes[level] = 0;
		mDimension[0][level] = 0;
		mDimension[1][level] = 0;
	}

	int face;
	for (face = 0; face < 6; ++face)
	{
		for (level = 0; level < mNumLevels; ++level)
		{
			glGenBuffers(1, &mBuffer[face][level]);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, mBuffer[face][level]);
			glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB, mNumLevelBytes[level], 0,
				usage);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

			mLockedMemory[face][level] = 0;
		}
		for (/**/; level < Texture::MM_MAX_MIPMAP_LEVELS; ++level)
		{
			mBuffer[face][level] = 0;
			mLockedMemory[face][level] = 0;
		}
	}

	glGenTextures(1, &mTexture);
	GLuint previousBind = BindTexture(Shader::ST_CUBE, mTexture);

	mIsCompressed = texture->IsCompressed();
	if (mIsCompressed)
	{
		for (face = 0; face < 6; ++face)
		{
			for (level = 0; level < mNumLevels; ++level)
			{
				glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
					level, mInternalFormat, mDimension[0][level],
					mDimension[1][level], 0, mNumLevelBytes[level], 0);
			}
		}
	}
	else
	{
		for (face = 0; face < 6; ++face)
		{
			for (level = 0; level < mNumLevels; ++level)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level,
					mInternalFormat, mDimension[0][level],
					mDimension[1][level], 0, mFormat, mType, 0);
			}
		}
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, previousBind);

	for (face = 0; face < 6; ++face)
	{
		for (level = 0; level < mNumLevels; ++level)
		{
			void* data = Lock(face, level, Buffer::BL_WRITE_ONLY);
			memcpy(data, texture->GetData(face, level),
				texture->GetNumLevelBytes(level));
			Unlock(face, level);
		}
	}
}
//----------------------------------------------------------------------------
PdrTextureCube::~PdrTextureCube ()
{
	for (int face = 0; face < 6; ++face)
	{
		for (int level = 0; level < mNumLevels; ++level)
		{
			glDeleteBuffers(1, &mBuffer[face][level]);
		}
	}
	glDeleteTextures(1, &mTexture);
}
//----------------------------------------------------------------------------
void PdrTextureCube::Enable (Renderer*, int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	mPreviousTexture = BindTexture(Shader::ST_CUBE, mTexture);
}
//----------------------------------------------------------------------------
void PdrTextureCube::Disable (Renderer*, int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mPreviousTexture);
}
//----------------------------------------------------------------------------
void* PdrTextureCube::Lock (int face, int level, Buffer::Locking mode)
{
	if (!mLockedMemory[face][level])
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, mBuffer[face][level]);
		mLockedMemory[face][level] = glMapBuffer(GL_PIXEL_UNPACK_BUFFER_ARB,
			gOGLBufferLocking[mode]);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

		mWriteLock[face][level] = (mode != Buffer::BL_READ_ONLY);
	}
	return mLockedMemory[face][level];
}
//----------------------------------------------------------------------------
void PdrTextureCube::Unlock (int face, int level)
{
	if (mLockedMemory[face][level])
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, mBuffer[face][level]);
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER_ARB);

		if (mWriteLock[face][level])
		{
			GLuint previousBind = BindTexture(Shader::ST_CUBE, mTexture);

			if (mIsCompressed)
			{
				glCompressedTexSubImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, 0, 0,
					mDimension[0][level], mDimension[1][level],
					mInternalFormat, mNumLevelBytes[level], 0);
			}
			else
			{
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level,
					0, 0, mDimension[0][level], mDimension[1][level], mFormat,
					mType, 0);
			}

			glBindTexture(GL_TEXTURE_CUBE_MAP, previousBind);
			mWriteLock[face][level] = false;
		}

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
		mLockedMemory[face][level] = 0;
	}
}
//----------------------------------------------------------------------------
