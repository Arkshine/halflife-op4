/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#ifndef CTFPLAY_GAMERULES_H
#define CTFPLAY_GAMERULES_H

/**
*	@brief Opposing Force CTF gamemode rules
*/
class CHalfLifeCTFplay : public CHalfLifeMultiplay
{
private:
	enum class StatsPhase
	{
		Nothing,
		SendTeam0,
		SendTeam1,
		SendTeam2,
		SendPlayers,
		OpenMenu
	};

public:
	CHalfLifeCTFplay();

	void Think() override;

	BOOL IsTeamplay() override { return TRUE; }
	BOOL IsCTF() override { return TRUE; }

	const char* GetGameDescription() override { return "OpFor CTF"; }

	BOOL ClientConnected( edict_t* pEntity, const char* pszName, const char* pszAddress, char* szRejectReason ) override;

	void InitHUD( CBasePlayer* pPlayer ) override;

	void ClientDisconnected( edict_t* pClient ) override;

	void UpdateGameMode( CBasePlayer* pPlayer ) override;

	BOOL FPlayerCanTakeDamage( CBasePlayer* pPlayer, CBaseEntity* pAttacker ) override;

	BOOL ShouldAutoAim( CBasePlayer* pPlayer, edict_t* target ) override;

	void PlayerSpawn( CBasePlayer* pPlayer ) override;

	void PlayerThink( CBasePlayer* pPlayer ) override;

	BOOL ClientCommand( CBasePlayer* pPlayer, const char* pcmd ) override;

	void ClientUserInfoChanged( CBasePlayer* pPlayer, char* infobuffer ) override;

	int IPointsForKill( CBasePlayer* pAttacker, CBasePlayer* pKilled ) override;

	void PlayerKilled( CBasePlayer* pVictim, entvars_t* pKiller, entvars_t* pInflictor ) override;

	void DeathNotice( CBasePlayer* pVictim, entvars_t* pKiller, entvars_t* pevInflictor ) override;

	BOOL CanHaveAmmo( CBasePlayer* pPlayer, const char* pszAmmoName, int iMaxCarry ) override;

	const char* GetTeamID( CBaseEntity* pEntity ) override;

	int PlayerRelationship( CBaseEntity* pPlayer, CBaseEntity* pTarget ) override;

	int CHalfLifeCTFplay::GetTeamIndex( const char* pTeamName ) override;

	const char* GetIndexedTeamName( int teamIndex ) override;

	BOOL IsValidTeam( const char* pTeamName ) override;

	void ChangePlayerTeam( CBasePlayer* pPlayer, const char* pCharName, BOOL bKill, BOOL bGib ) override;

	const char* SetDefaultPlayerTeam( CBasePlayer* pPlayer ) override;

	const char* GetCharacterType( int iTeamNum, int iCharNum ) override;

	int GetNumTeams() override;

	const char* TeamWithFewestPlayers() override;

	BOOL TeamsBalanced() override;

	void GoToIntermission() override;

private:
	void SendTeamStatInfo( int iTeamNum );
	void SendPlayerStatInfo( CBasePlayer* pPlayer );

	void RecountTeams();

private:
	bool m_DisableDeathMessages = false;
	bool m_DisableDeathPenalty = false;
	bool m_fRefreshScores = false;
	float m_flNextStatsSend;
	StatsPhase m_iStatsPhase = StatsPhase::SendTeam0;
	int m_iStatsPlayer;
};

#endif
