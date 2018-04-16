// Fill out your copyright notice in the Description page of Project Settings.

#include "PhotoPlayer.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"

// Sets default values
APhotoPlayer::APhotoPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	collisionCapsule->SetCollisionProfileName("BlockAll");
	RootComponent = collisionCapsule;
	
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->AttachTo(RootComponent);
	camera->SetRelativeLocation(FVector(0.0f, 0.0f, 32.0f));

	snapshotComponent = CreateDefaultSubobject<USnapshotComponent>("Snapshot Component");
	photoCameraComponent = CreateDefaultSubobject<UPhotoCameraComponent>("Photo Component");

	movementComponent = CreateDefaultSubobject<UVelocityMovementComponent>("Movement Component");
	movementComponent->gravitySpeed = 0.25f;
	movementComponent->friction = 0.2f;
	movementComponent->maxWalkSpeed = 8.0f;
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

	float deltaTick = DeltaTime * 60.0f;

	if (lockOnActor == nullptr) {
		SetActorRotation(FRotator(0.0f, cameraPan, 0.0f));
		camera->SetRelativeRotation(FRotator(cameraTilt, 0.0f, 0.0f));
	}
	else {
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), lockOnActor->GetActorLocation());
		SetActorRotation(FRotator(0, targetRotation.Yaw, 0));
		camera->SetRelativeRotation(FRotator(targetRotation.Pitch, 0, 0));
	}

	photoCameraComponent->SetWorldLocation(camera->GetComponentLocation());
	photoCameraComponent->SetWorldRotation(camera->GetComponentRotation()); 

	if (movementComponent->IsOnGround()) {
		movementComponent->AddVelocity((GetActorForwardVector()*yInputAxis*movementComponent->acceleration*deltaTick));
		movementComponent->AddVelocity((GetActorRightVector()*xInputAxis*movementComponent->acceleration*deltaTick));
	}
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
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APhotoPlayer::JumpInput);
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
	photoCameraComponent->TakePhoto();
}

void APhotoPlayer::Test2Function() {
	photoCameraComponent->ExportPhotos();
}

void APhotoPlayer::JumpInput() {

}