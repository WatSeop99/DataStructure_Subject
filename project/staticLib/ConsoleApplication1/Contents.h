#pragma once

#include <iostream>
#include <string>

class Contents
{
public:
	enum class eContentsType
	{
		Image,
		Music,
		None
	};

	Contents();

	eContentsType GetType() const;
	void SetType(eContentsType type);
	virtual std::string Run(std::string name, std::string path) = 0;

private:
	eContentsType mType;
};

class MusicFile : public Contents
{
public:
	MusicFile(std::string title = "", std::string artist = "",
		std::string album = "", std::string lyrics = "");

	std::string GetAlbum() const;
	std::string GetArtist() const;
	std::string GetLyrics() const;
	std::string GetTitle() const;
	std::string Run(std::string name, std::string path);
	void SetAlbum(std::string album);
	void SetArtist(std::string artist);
	void SetLyrics(std::string lyrics);
	void SetTitle(std::string title);
	void SetAlbumFromWindow(const char* album);
	void SetArtistFromWindow(const char* artist);
	void SetTitleFromWindow(const char* title);

private:
	std::string mTitle;
	std::string mArtist;
	std::string mAlbum;
	std::string mLyrics;
};

class ImageFile : public Contents
{
public:
	ImageFile(std::string _event = "");

	std::string GetEvent() const;
	std::string Run(std::string name, std::string path);
	void SetEvent(std::string _event);
private:
	std::string mEvent;
};