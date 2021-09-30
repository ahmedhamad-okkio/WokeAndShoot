// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WokeAndShootPlayerController.generated.h"

class UCameraComponent;
struct FKillInfo;
UCLASS()
class WOKEANDSHOOT_API AWokeAndShootPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDeathScreenWidget> DeathScreenClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> EscapeScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ScoreboardClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UKillFeedWidget> KillFeedClass;

	UPROPERTY()
	UDeathScreenWidget* DeathScreen = nullptr;

	UPROPERTY()
	UUserWidget* EscapeScreen = nullptr;

	UPROPERTY()
	UUserWidget* Scoreboard = nullptr;

	UPROPERTY()
	UUserWidget* HUD = nullptr;

	UPROPERTY()
	UKillFeedWidget* KillFeed = nullptr;

	FString PlayerName;

	float InternalSensitivity;

	bool IsPossessing = false;

protected:
	virtual void BeginPlay()override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupInputComponent() override;
	virtual void OnRep_PlayerState() override;

private:
	AWokeAndShootPlayerController();

	void ShowEscapeMenu();
	void ShowScoreboard();
	void HideScoreboard();
	void ShowDeathScreen();
	void HideDeathScreen();
	void ShowHUD();
	void HideHUD();

public:
	void ClientReceiveSpawn();
	void ClientReceiveDeath();
	void ClientReceiveKillInfo(const FKillInfo& NewKillInfo);
	void ClientHandlePawnDeath();
	
	UFUNCTION(BlueprintPure, Category="Player Information")
	FString GetLocalPlayerName() const;
	UFUNCTION(BlueprintCallable, Category="Player Information")
	void SetLocalPlayerName(const FString& NewName);

	UFUNCTION(BlueprintPure, Category="Player Settings")
	float GetSensitivity() const;
	UFUNCTION(BlueprintCallable, Category="Player Settings")
	void SetSensitivity(float NewSensitivity);

private:
	// Network
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_ChangeName(const FString& NewName);
	bool Server_ChangeName_Validate(const FString& NewName);
	void Server_ChangeName_Implementation(const FString& NewName);
};
