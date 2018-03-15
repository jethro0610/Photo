// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Exporters/TextureExporterBMP.h"
#include "PhotoCameraComponent.generated.h"

USTRUCT() 
struct FPhotograph {
	GENERATED_BODY()

	UPROPERTY()
	UTextureRenderTarget2D* photograph;

	FPhotograph() {
		photograph = nullptr;
	}

	FPhotograph(UTextureRenderTarget2D* inputPhotograph) {
		photograph = DuplicateObject<UTextureRenderTarget2D>(inputPhotograph, inputPhotograph->GetOuter(), FName(NAME_None));
	}
};

/**
 * 
 */
UCLASS()
class PHOTO_API UPhotoCameraComponent : public USceneCaptureComponent2D
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UPhotoCameraComponent();
	
	void TakePhoto();
	void ExportPhotos();

	TArray<FPhotograph> currentPhotographs;
};
