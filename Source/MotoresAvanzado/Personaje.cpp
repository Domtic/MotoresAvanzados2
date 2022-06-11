// Fill out your copyright notice in the Description page of Project Settings.


#include "Personaje.h"

// Sets default values
APersonaje::APersonaje()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
    cameraBoom->SetupAttachment(RootComponent);
    cameraBoom->TargetArmLength = 300.f;
    cameraBoom->bUsePawnControlRotation = true;
    //Acomodar la cámara
    cameraBoom->SocketOffset = FVector(0.f, 50.f, 50.f);


    followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
    //Esto lo deja al final de la raiz del objeto al que lo estas agregando
    followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
    followCamera->bUsePawnControlRotation = false;

   // GetCharacterMovement()->RotationRate
}

// Called when the game starts or when spawned
void APersonaje::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APersonaje::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APersonaje::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("Vertical", this, &APersonaje::MoveForward);
    PlayerInputComponent->BindAxis("Horizontal", this, &APersonaje::MoveHorizontal);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released ,this, &ACharacter::StopJumping);
}

void APersonaje::MoveForward(float value)
{
    if (IsControllerWorking(value))
    {
        rotation = Controller->GetControlRotation();
        yawRotation = FRotator(0.f, rotation.Yaw, 0.f);
        direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(direction, value);
    }
}


void APersonaje::MoveHorizontal(float value)
{
    if (IsControllerWorking(value))
    {
        rotation = Controller->GetControlRotation();
        yawRotation = FRotator(0.f, rotation.Yaw, 0.f);
        direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(direction, value);
    }
}

bool APersonaje::IsControllerWorking(float& value) const {
    return Controller != nullptr && value != 0.f;
}