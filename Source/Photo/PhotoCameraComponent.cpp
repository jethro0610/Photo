#include "PhotoCameraComponent.h"
#include "Classes/Kismet/KismetRenderingLibrary.h"

UPhotoCameraComponent::UPhotoCameraComponent()
{
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