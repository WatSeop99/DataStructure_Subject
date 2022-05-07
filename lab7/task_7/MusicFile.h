#pragma once

#include "ContentsType.h"

class MusicFile : public ContentsType {
public:
	MusicFile(std::string _title = "", std::string _artist = "", std::string _album = "")
		: title(_title), artist(_artist), album(_album) { }

	void setRecord();
	void setTitle(std::string _title) { title = _title; }
	void steArtist(std::string _artist) { artist = _artist; }
	void setAlbum(std::string _album) { album = _album; }
	std::string getTitle() const { return title; }
	std::string getAritst() const { return artist; }
	std::string getalbum() const { return album; }
	void run(std::string _name);
	int getCommand();
	void displayMusicInfo();
private:
	std::string title;
	std::string artist;
	std::string album;