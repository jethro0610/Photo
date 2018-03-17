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
	CaptureScene();

	UPhotograph* photoToAdd = NewObject<UPhotograph>();
	photoToAdd->UpdateFromRenderTarget(TextureTarget);

	currentPhotographs.Add(photoToAdd);
}

void UPhotoCameraComponent::ExportPhotos() {
	for (int i = 0; i < currentPhotographs.Num(); i++) {
		FString filePath = "C:/Users/Jethro/Test/" + FString::FromInt(i + 1) + ".png";
		FFileHelper::SaveArrayToFile(currentPhotographs[i]->image, *filePath);
	}
}