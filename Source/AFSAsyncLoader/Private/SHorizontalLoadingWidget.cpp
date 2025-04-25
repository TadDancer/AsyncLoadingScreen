#include "SHorizontalLoadingWidget.h"
#include "LoadingScreenSettings.h"
#include "ShaderPipelineCache.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Images/SImage.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"

void SHorizontalLoadingWidget::Construct(const FArguments& InArgs, const FLoadingWidgetSettings& Settings)
{
    // Settings für Tick sichern
    LoadingSettings = Settings;
    bPlayReverse = Settings.ImageSequenceSettings.bPlayReverse;

    // Initialer DisplayText
    FText DisplayText;
    if (Settings.bShowRemainingPrecompiles)
    {
        DisplayText = FText::Format(
            NSLOCTEXT("AFSAsyncLoader", "PrecompileCount", "{0} {1}"),
            FShaderPipelineCache::NumPrecompilesRemaining(),
            Settings.ShaderCaption
        );
    }
    else
    {
        DisplayText = Settings.LoadingText;
    }

    // Root ist eine HorizontalBox
    TSharedRef<SHorizontalBox> Root = SNew(SHorizontalBox);

    // Loading Icon Widget bauen
    ConstructLoadingIcon(Settings);

    // Sichtbarkeit des Textes
    EVisibility LoadingTextVisibility = Settings.LoadingText.IsEmpty()
        ? EVisibility::Collapsed
        : EVisibility::SelfHitTestInvisible;

    // Wenn Text rechts positioniert
    if (Settings.bLoadingTextRightPosition)
    {
        Root->AddSlot()
            .HAlign(Settings.LoadingIconAlignment.HorizontalAlignment)
            .VAlign(Settings.LoadingIconAlignment.VerticalAlignment)
            .AutoWidth()
            [
                LoadingIcon
            ];

        Root->AddSlot()
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            .AutoWidth()
            [
                SNew(SSpacer)
                .Size(FVector2D(Settings.Space, 0.0f))
            ];

        Root->AddSlot()
            .HAlign(Settings.TextAlignment.HorizontalAlignment)
            .VAlign(Settings.TextAlignment.VerticalAlignment)
            .AutoWidth()
            [
                SAssignNew(LoadingTextBlock, STextBlock)
                .Visibility(LoadingTextVisibility)
                .ColorAndOpacity(Settings.Appearance.ColorAndOpacity)
                .Font(Settings.Appearance.Font)
                .ShadowOffset(Settings.Appearance.ShadowOffset)
                .ShadowColorAndOpacity(Settings.Appearance.ShadowColorAndOpacity)
                .Justification(Settings.Appearance.Justification)
                .Text(DisplayText)
            ];
    }
    else // Text links
    {
        Root->AddSlot()
            .HAlign(Settings.TextAlignment.HorizontalAlignment)
            .VAlign(Settings.TextAlignment.VerticalAlignment)
            .AutoWidth()
            [
                SAssignNew(LoadingTextBlock, STextBlock)
                .Visibility(LoadingTextVisibility)
                .ColorAndOpacity(Settings.Appearance.ColorAndOpacity)
                .Font(Settings.Appearance.Font)
                .ShadowOffset(Settings.Appearance.ShadowOffset)
                .ShadowColorAndOpacity(Settings.Appearance.ShadowColorAndOpacity)
                .Justification(Settings.Appearance.Justification)
                .Text(DisplayText)
            ];

        Root->AddSlot()
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            .AutoWidth()
            [
                SNew(SSpacer)
                .Size(FVector2D(Settings.Space, 0.0f))
            ];

        Root->AddSlot()
            .HAlign(Settings.LoadingIconAlignment.HorizontalAlignment)
            .VAlign(Settings.LoadingIconAlignment.VerticalAlignment)
            .AutoWidth()
            [
                LoadingIcon
            ];
    }

    // Root in ChildSlot
    ChildSlot
    [
        Root
    ];
}

void SHorizontalLoadingWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
    SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

    if (LoadingTextBlock.IsValid() && LoadingSettings.bShowRemainingPrecompiles)
    {

        FText DisplayText = FText::Format(
            NSLOCTEXT("AFSAsyncLoader", "PrecompileCount", "{0} {1}"),
            FShaderPipelineCache::NumPrecompilesRemaining(),
            LoadingSettings.ShaderCaption
        );
        LoadingTextBlock->SetText(DisplayText);
    }
}