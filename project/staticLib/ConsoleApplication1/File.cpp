#include "File.h"

File::File(Contents::eContentsType type)
{
	mContentsType = type;
	mContents = nullptr;
}

File::File(Item& data)
{
	File* input = dynamic_cast<File*>(&data);

	mName = input->mName;
	mPath = input->mPath;
	mCreationTime = input->mCreationTime;
	mModifiedTime = GenTime();
	mType = input->mType;

	switch (input->GetContentsType())
	{
	case Contents::eContentsType::Image:
		mContentsType = Contents::eContentsType::Image;
		mContents = new ImageFile;
		break;
	case Contents::eContentsType::Music:
		mContentsType = Contents::eContentsType::Music;
		mContents = new MusicFile;
		break;
	default:
		mContentsType = Contents::eContentsType::None;
		mContents = nullptr;
		break;
	}
}

File::~File()
{
	if (mContents != nullptr)
	{
		delete mContents;
		mContents = nullptr;
	}
}

void File::GetContents(Contents::eContentsType type, void* outParam) const
{
	switch (type)
	{
	case Contents::eContentsType::Image:
		ImageFile* image = dynamic_cast<ImageFile*>(mContents);

		if (((struct Parameter*)outParam)->Event != nullptr)
		{
			delete ((struct Parameter*)outParam)->Event;
			((struct Parameter*)outParam)->Event = nullptr;
		}

		((struct Parameter*)outParam)->Event = new char[image->GetEvent().length() + 1];
		strcpy_s(((struct Parameter*)outParam)->Event,
			image->GetEvent().length() + 1,
			image->GetEvent().c_str());
		break;
	case Contents::eContentsType::Music:
		MusicFile* music = dynamic_cast<MusicFile*>(mContents);

		if (((struct Parameter*)outParam)->Album != nullptr)
		{
			delete ((struct Parameter*)outParam)->Album;
			((struct Parameter*)outParam)->Album = nullptr;
		}
		if (((struct Parameter*)outParam)->Artist != nullptr)
		{
			delete ((struct Parameter*)outParam)->Artist;
			((struct Parameter*)outParam)->Artist = nullptr;
		}
		if (((struct Parameter*)outParam)->Lyrics != nullptr)
		{
			delete ((struct Parameter*)outParam)->Lyrics;
			((struct Parameter*)outParam)->Lyrics = nullptr;
		}

		((struct Parameter*)outParam)->Album = new char[music->GetAlbum().length() + 1];
		((struct Parameter*)outParam)->Artist = new char[music->GetArtist().length() + 1];
		((struct Parameter*)outParam)->Lyrics = new char[music->GetLyrics().length() + 1];
		strcpy_s(((struct Parameter*)outParam)->Album,
			music->GetAlbum().length() + 1,
			music->GetAlbum().c_str());
		strcpy_s(((struct Parameter*)outParam)->Artist,
			music->GetArtist().length() + 1,
			music->GetArtist().c_str());
		strcpy_s(((struct Parameter*)outParam)->Lyrics,
			music->GetLyrics().length() + 1,
			music->GetLyrics().c_str());
		break;
	default:
		break;
	}
}

Contents::eContentsType File::GetContentsType() const
{
	return mContentsType;
}

void File::SetContents(Contents::eContentsType type, void* param)
{
	switch (type)
	{
	case Contents::eContentsType::Image:
		ImageFile* image = dynamic_cast<ImageFile*>(mContents);

		if (((struct Parameter*)param)->Event != nullptr)
		{
			image->SetEvent((std::string)((struct Parameter*)param)->Event);
		}
		break;
	case Contents::eContentsType::Music:
		MusicFile* music = dynamic_cast<MusicFile*>(mContents);

		music->SetTitle(GetName());
		if (((struct Parameter*)param)->Album != nullptr)
		{
			music->SetAlbum((std::string)((struct Parameter*)param)->Album);
		}
		if (((struct Parameter*)param)->Artist != nullptr)
		{
			music->SetArtist((std::string)((struct Parameter*)param)->Artist);
		}
		if (((struct Parameter*)param)->Lyrics != nullptr)
		{
			music->SetLyrics((std::string)((struct Parameter*)param)->Lyrics);
		}
		break;
	default:
		break;
	}
}

void File::SetContentsType(Contents::eContentsType type)
{
	mContentsType = type;

	if (mContents != nullptr)
	{
		delete mContents;
		mContents = nullptr;
	}
	switch (type)
	{
	case Contents::eContentsType::Image:
		mContents = new ImageFile;
		break;
	case Contents::eContentsType::Music:
		mContents = new MusicFile;
		break;
	default:
		break;
	}
}

Item& File::operator=(Item& data)
{
	File* input = dynamic_cast<File*>(&data);

	mName = input->mName;
	mPath = input->mPath;
	mCreationTime = input->mCreationTime;
	mModifiedTime = GenTime();
	mType = input->mType;
	
	if (mContents != nullptr)
	{
		delete mContents;
		mContents = nullptr;
	}

	switch (input->GetContentsType())
	{
	case Contents::eContentsType::Image:
		mContentsType = Contents::eContentsType::Image;
		mContents = new ImageFile;
		break;
	case Contents::eContentsType::Music:
		mContentsType = Contents::eContentsType::Music;
		mContents = new MusicFile;
		break;
	default:
		mContentsType = Contents::eContentsType::None;
		mContents = nullptr;
		break;
	}

	struct Parameter param;
	param.Album = nullptr;
	param.Artist = nullptr;
	param.Event = nullptr;
	param.Lyrics = nullptr;

	input->GetContents(mContentsType, (void*)(&param));
	SetContents(mContentsType, (void*)(&param));
	
	switch (mContentsType)
	{
	case Contents::eContentsType::Image:
		delete param.Event;
		param.Event = nullptr;
		break;
	case Contents::eContentsType::Music:
		delete param.Album;
		delete param.Artist;
		delete param.Lyrics;
		param.Album = nullptr;
		param.Artist = nullptr;
		param.Lyrics = nullptr;
		break;
	default:
		break;
	}

	return *this;
}