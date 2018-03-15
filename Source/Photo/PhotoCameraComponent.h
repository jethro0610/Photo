// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Exporters/TextureExporterBMP.h"
#include "PhotoCameraComponent.generated.h"

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
};
