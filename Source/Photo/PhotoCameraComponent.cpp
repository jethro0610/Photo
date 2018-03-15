// Fill out your copyright notice in the Description page of Project Settings.

#include "PhotoCameraComponent.h"
#include "Classes/Kismet/KismetRenderingLibrary.h"

// Sets default values for this component's properties
UPhotoCameraComponent::UPhotoCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UPhotoCameraComponent::TakePhoto() {
	//TextureTarget->AdjustBrightness = 255.0f;
	CaptureScene();
	//TextureTarget->AdjustBrightness = 255.0f;
	//UKismetRenderingLibrary::ExportRenderTarget(this, TextureTarget, "C:/Users/Jethro", "render.png");

	currentPhotographs.Add(FPhotograph(TextureTarget));
}

void UPhotoCameraComponent::ExportPhotos() {
	for (int i = 0; i < currentPhotographs.Num(); i++) {
		UKismetRenderingLibrary::ExportRenderTarget(this, TextureTarget, "C:/Users/Jet/Test", FString::FromInt(i) + ".png");
	}
}