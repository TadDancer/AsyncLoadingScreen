/************************************************************************************
 *																					*
 * Copyright (C) 2020 Truong Bui.													*
 * Website:	https://github.com/truong-bui/AsyncLoadingScreen						*
 * Licensed under the MIT License. See 'LICENSE' file for full license information. *
 *																					*
 ************************************************************************************/


#include "AFSAsyncLoaderLibrary.h"
#include "MoviePlayer.h"
#include "AFSAsyncLoader.h"

int32 UAFSAsyncLoaderLibrary::DisplayBackgroundIndex = -1;
int32 UAFSAsyncLoaderLibrary::DisplayTipTextIndex = -1;
int32 UAFSAsyncLoaderLibrary::DisplayMovieIndex = -1;
bool  UAFSAsyncLoaderLibrary::bShowLoadingScreen = true;

void UAFSAsyncLoaderLibrary::SetDisplayBackgroundIndex(int32 BackgroundIndex)
{
	UAFSAsyncLoaderLibrary::DisplayBackgroundIndex = BackgroundIndex;
}

void UAFSAsyncLoaderLibrary::SetDisplayTipTextIndex(int32 TipTextIndex)
{
	UAFSAsyncLoaderLibrary::DisplayTipTextIndex = TipTextIndex;
}

void UAFSAsyncLoaderLibrary::SetDisplayMovieIndex(int32 MovieIndex)
{
	UAFSAsyncLoaderLibrary::DisplayMovieIndex = MovieIndex;	
}

void UAFSAsyncLoaderLibrary::SetEnableLoadingScreen(bool bIsEnableLoadingScreen)
{
	bShowLoadingScreen = bIsEnableLoadingScreen;
}

void UAFSAsyncLoaderLibrary::StopLoadingScreen()
{
	GetMoviePlayer()->StopMovie();
}

void UAFSAsyncLoaderLibrary::PreloadBackgroundImages()
{
	if (FAFSAsyncLoaderModule::IsAvailable())
	{
		FAFSAsyncLoaderModule& LoadingScreenModule = FAFSAsyncLoaderModule::Get();
		if (LoadingScreenModule.IsPreloadBackgroundImagesEnabled())
		{
			LoadingScreenModule.LoadBackgroundImages();
		}		
	}
}

void UAFSAsyncLoaderLibrary::RemovePreloadedBackgroundImages()
{
	if (FAFSAsyncLoaderModule::IsAvailable())
	{
		FAFSAsyncLoaderModule& LoadingScreenModule = FAFSAsyncLoaderModule::Get();
		LoadingScreenModule.RemoveAllBackgroundImages();
	}
}

