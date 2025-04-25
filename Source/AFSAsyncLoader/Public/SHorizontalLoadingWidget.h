/************************************************************************************
*																					*
 * Copyright (C) 2020 Truong Bui.													*
 * Website:	https://github.com/truong-bui/AsyncLoadingScreen						*
 * Licensed under the MIT License. See 'LICENSE' file for full license information. *
 *																					*
 ************************************************************************************/

#pragma once

#include "Widgets/Text/STextBlock.h"
#include "SLoadingWidget.h"

struct FLoadingWidgetSettings;

/**
 *  Horizontal Loading Widget
 */
class SHorizontalLoadingWidget : public SLoadingWidget
{
public:
	SHorizontalLoadingWidget() = default;
	virtual ~SHorizontalLoadingWidget() = default;

	// Tick override for dynamic text updates
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	SLATE_BEGIN_ARGS(SHorizontalLoadingWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FLoadingWidgetSettings& Settings);

private:
	// Kopie der Settings für Tick
	FLoadingWidgetSettings LoadingSettings;

	// Pointer auf das Text-Widget
	TSharedPtr<STextBlock> LoadingTextBlock;
};
