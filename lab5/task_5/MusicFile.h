#pragma once

#include "ItemType.h"


class MusicFile : public ItemType {
private:
	std::string title;
	std::string artist;
	std::string album;
public:
	MusicFile(std::string _title= "\0", std::string _artist = "\0", std::string _album = "\0") : title(_title), artist(_artist), album(_album)
	{ }
	~MusicFile() { }

	void SetRecord();
	void SetTitle(std::string _title) { title = _title; }
	void SetArtist(std::string _artist) { artist = _artist; }
	void SetAlbum(std::string _album) { album = _album; }
	std::string GetTitle() const { return title; }
	std::string GetArtist() const { return artist; }
	std::string GetAlbum() const { return album; }
	void Run(std::string name);
	int GetCommand();
	void DisplayMusicInfo();
};