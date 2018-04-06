// Fill out your copyright notice in the Description page of Project Settings.

#include "PhotoPlayer.h"
#include "PlayerMovementComponent.h"
#include "Engine.h"
#include "Components/InputComponent.h"

// Sets default values
APhotoPlayer::APhotoPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionBox = CreateDefaultSubobject<UBoxComponent>("Collider");
	collisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 64.0f));
	RootComponent = collisionBox;
	
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->AttachTo(RootComponent);
	camera->SetRelativeLocation(FVector(0.0f, 0.0f, 32.0f));

	snapshotComponent = CreateDefaultSubobject<USnapshotComponent>("Snapshot Component");
	photoCameraComponent = CreateDefaultSubobject<UPhotoCameraComponent>("Photo Component");

	movementComponent = CreateDefaultSubobject<UPlayerMovementComponent>("Movement Component");
	movementComponent->parentPlayer = this;
}

// Called when the game starts or when spawned
void APhotoPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhotoPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorRotation(FRotator(0.0f, cameraPan, 0.0f));
	camera->SetRelativeRotation(FRotator(cameraTilt, 0.0f, 0.0f));

	photoCameraComponent->SetWorldLocation(camera->GetComponentLocation());
	photoCameraComponent->SetWorldRotation(camera->GetComponentRotation());
}

// Called to bind functionality to input
void APhotoPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Mouse X", this, &APhotoPlayer::UpdateMouseX);
	PlayerInputComponent->BindAxis("Mouse Y", this, &APhotoPlayer::UpdateMouseY);
	PlayerInputComponent->BindAxis("Move X", this, &APhotoPlayer::UpdateInputX);
	PlayerInputComponent->BindAxis("Move Y", this, &APhotoPlayer::UpdateInputY);
	PlayerInputComponent->BindAction("Test Input", EInputEvent::IE_Released, this, &APhotoPlayer::TestInputFunction);
	PlayerInputComponent->BindAction("Test 2", EInputEvent::IE_Released, this, &APhotoPlayer::Test2Function);
}

void APhotoPlayer::UpdateMouseX(float axisValue) {
	cameraPan += axisValue;
}

void APhotoPlayer::UpdateMouseY(float axisValue) {
	cameraTilt += axisValue;
	cameraTilt = FMath::Clamp(cameraTilt, -85.0f, 85.0f);
}

void APhotoPlayer::UpdateInputX(float axisValue) {
	xInputAxis = axisValue;
}

void APhotoPlayer::UpdateInputY(float axisValue) {
	yInputAxis = axisValue;
}

void APhotoPlayer::TestInputFunction() {
	//snapshotComponent->TakeSnapshot();
	photoCameraComponent->TakePhoto();
}

void APhotoPlayer::Test2Function() {
	//snapshotComponent->TakeSnapshot();
	photoCameraComponent->ExportPhotos();
}

bool APhotoPlayer::IsOnGround(float maxDistance) {
	FHitResult traceOutput;
	FCollisionQueryParams ignoreParams;
	ignoreParams.AddIgnoredActor(this);
	ignoreParams.AddIgnoredComponent(collisionBox);
	GetWorld()->LineTraceSingleByChannel(traceOutput, GetActorLocation(), GetActorLocation() - (GetActorUpVector() * maxDistance), ECC_WorldDynamic, ignoreParams);
	return traceOutput.IsValidBlockingHit();
}

FVector APhotoPlayer::GetGroundNormal(float maxDistance) {
	FHitResult traceOutput;
	FCollisionQueryParams ignoreParams;
	ignoreParams.AddIgnoredActor(this);
	ignoreParams.AddIgnoredComponent(collisionBox);
	GetWorld()->LineTraceSingleByChannel(traceOutput, GetActorLocation(), GetActorLocation() - (GetActorUpVector() * maxDistance), ECC_WorldDynamic, ignoreParams);
	return traceOutput.Normal;
}