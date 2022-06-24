#include "Contents.h"

Contents::Contents()
{
	mType = Contents::eContentsType::None;
}

Contents::eContentsType Contents::GetType() const
{
	return mType;
}

void Contents::SetType(Contents::eContentsType type)
{
	mType = type;
}

MusicFile::MusicFile(std::string title, std::string artist,
	std::string album, std::string lyrics)
{
	mTitle = title;
	mArtist = artist;
	mAlbum = album;
	mLyrics = lyrics;
}

std::string MusicFile::GetAlbum() const
{
	return mAlbum;
}

std::string MusicFile::GetArtist() const
{
	return mArtist;
}

std::string MusicFile::GetLyrics() const
{
	return mLyrics;
}

std::string MusicFile::GetTitle() const
{
	return mTitle;
}

std::string MusicFile::Run(std::string name, std::string path)
{
	std::string runFile = path + name + '\\';
	return runFile;
}

void MusicFile::SetAlbum(std::string album)
{
	mAlbum = album;
}

void MusicFile::SetArtist(std::string artist)
{
	mArtist = artist;
}

void MusicFile::SetLyrics(std::string lyrics)
{
	mLyrics = lyrics;
}

void MusicFile::SetTitle(std::string title)
{
	mTitle = title;
}

void MusicFile::SetAlbumFromWindow(const char* album)
{
	mAlbum = album;
}

void MusicFile::SetArtistFromWindow(const char* artist)
{
	mArtist = artist;
}

void MusicFile::SetTitleFromWindow(const char* title)
{
	mTitle = title;
}

ImageFile::ImageFile(std::string _event)
{
	mEvent = _event;
}

std::string ImageFile::GetEvent() const
{
	return mEvent;
}

std::string ImageFile::Run(std::string name, std::string path)
{
	std::string runFile = path + name + '\\';
	return runFile;
}

void ImageFile::SetEvent(std::string _event)
{
	mEvent = _event;
}