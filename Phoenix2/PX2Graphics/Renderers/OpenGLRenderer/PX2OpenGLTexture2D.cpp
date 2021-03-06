/*
*
* 文件名称	：	PX2OpenGLTexture2D.cpp
*
*/

#include "PX2OpenGLTexture2D.hpp"
#include "PX2OpenGLMapping.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PdrTexture2D::PdrTexture2D (Renderer*, const Texture2D* texture)
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

		glGenBuffers(1, &mBuffer[level]);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, mBuffer[level]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB, mNumLevelBytes[level], 0,
			usage);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

		mDimension[0][level] = texture->GetDimension(0, level);
		mDimension[1][level] = texture->GetDimension(1, level);
		mLockedMemory[level] = 0;
		mWriteLock[level] = false;
	}
	for (/**/; level < Texture::MM_MAX_MIPMAP_LEVELS; ++level)
	{
		mBuffer[level] = 0;
		mNumLevelBytes[level] = 0;
		mDimension[0][level] = 0;
		mDimension[1][level] = 0;
		mLockedMemory[level] = 0;
		mWriteLock[level] = false;
	}

	// 创建贴图
	glGenTextures(1, &mTexture);
	GLuint previousBind = BindTexture(Shader::ST_2D, mTexture);

	// 创建mipmap
	mIsCompressed = texture->IsCompressed();
	if (mIsCompressed)
	{
		for (level = 0; level < mNumLevels; ++level)
		{
			glCompressedTexImage2D(GL_TEXTURE_2D, level, mInternalFormat,
				mDimension[0][level], mDimension[1][level], 0,
				mNumLevelBytes[level], 0);
		}
	}
	else
	{
		for (level = 0; level < mNumLevels; ++level)
		{
			glTexImage2D(GL_TEXTURE_2D, level, mInternalFormat,
				mDimension[0][level], mDimension[1][level], 0, mFormat,
				mType, 0);
		}
	}

	glBindTexture(GL_TEXTURE_2D, previousBind);

	for (level = 0; level < mNumLevels; ++level)
	{
		void* data = Lock(level, Buffer::BL_WRITE_ONLY);
		memcpy(data, texture->GetData(level),
			texture->GetNumLevelBytes(level));
		Unlock(level);
	}
}
//----------------------------------------------------------------------------
PdrTexture2D::~PdrTexture2D ()
{
	for (int level = 0; level < mNumLevels; ++level)
	{
		glDeleteBuffers(1, &mBuffer[level]);
	}
	glDeleteTextures(1, &mTexture);
}
//----------------------------------------------------------------------------
void PdrTexture2D::Enable (Renderer*,int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	mPreviousTexture = BindTexture(Shader::ST_2D, mTexture);
}
//----------------------------------------------------------------------------
void PdrTexture2D::Disable (Renderer*,int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, mPreviousTexture);
}
//----------------------------------------------------------------------------
void* PdrTexture2D::Lock (int level, Buffer::Locking mode)
{
	if (!mLockedMemory[level])
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, mBuffer[level]);
		mLockedMemory[level] = glMapBuffer(GL_PIXEL_UNPACK_BUFFER_ARB,
			gOGLBufferLocking[mode]);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

		mWriteLock[level] = (mode != Buffer::BL_READ_ONLY);
	}
	return mLockedMemory[level];
}
//----------------------------------------------------------------------------
void PdrTexture2D::Unlock (int level)
{
	if (mLockedMemory[level])
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, mBuffer[level]);
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER_ARB);

		if (mWriteLock[level])
		{
			GLuint previousBind = BindTexture(Shader::ST_2D, mTexture);

			if (mIsCompressed)
			{
				glCompressedTexSubImage2D(GL_TEXTURE_2D, level, 0, 0,
					mDimension[0][level], mDimension[1][level],
					mInternalFormat, mNumLevelBytes[level], 0);
			}
			else
			{
				glTexSubImage2D(GL_TEXTURE_2D, level, 0, 0,
					mDimension[0][level], mDimension[1][level], mFormat,
					mType, 0);
			}

			glBindTexture(GL_TEXTURE_2D, previousBind);
			mWriteLock[level] = false;
		}

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
		mLockedMemory[level] = 0;
	}
}
//----------------------------------------------------------------------------
