/* IDirectMusicWaveTrack Implementation
 *
 * Copyright (C) 2003-2004 Rok Mandeljc
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "dmime_private.h"

WINE_DEFAULT_DEBUG_CHANNEL(dmime);

/*****************************************************************************
 * IDirectMusicWaveTrack implementation
 */
/* IDirectMusicWaveTrack IUnknown part: */
static HRESULT WINAPI IDirectMusicWaveTrack_IUnknown_QueryInterface (LPUNKNOWN iface, REFIID riid, LPVOID *ppobj) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, UnknownVtbl, iface);
	TRACE("(%p, %s, %p)\n", This, debugstr_dmguid(riid), ppobj);

	if (IsEqualIID (riid, &IID_IUnknown)) {
		*ppobj = &This->UnknownVtbl;
		IUnknown_AddRef (iface);
		return S_OK;
	} else if (IsEqualIID (riid, &IID_IDirectMusicTrack)
	  || IsEqualIID (riid, &IID_IDirectMusicTrack8)) {
		*ppobj = (LPDIRECTMUSICTRACK8)&This->TrackVtbl;
		IUnknown_AddRef (iface);
		return S_OK;
	} else if (IsEqualIID (riid, &IID_IPersistStream)) {
		*ppobj = &This->PersistStreamVtbl;
		IUnknown_AddRef (iface);
		return S_OK;
	}
	
	WARN("(%p, %s, %p): not found\n", This, debugstr_dmguid(riid), ppobj);
	return E_NOINTERFACE;
}

static ULONG WINAPI IDirectMusicWaveTrack_IUnknown_AddRef (LPUNKNOWN iface) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, UnknownVtbl, iface);
        ULONG ref = InterlockedIncrement(&This->ref);

	TRACE("(%p) : AddRef from %d\n", This, ref - 1);

	DMIME_LockModule();

	return ref;
}

static ULONG WINAPI IDirectMusicWaveTrack_IUnknown_Release (LPUNKNOWN iface) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, UnknownVtbl, iface);
	ULONG ref = InterlockedDecrement(&This->ref);
	TRACE("(%p) : ReleaseRef to %d\n", This, ref);
	
	if (ref == 0) {
		HeapFree(GetProcessHeap(), 0, This);
	}

	DMIME_UnlockModule();
	
	return ref;
}

static const IUnknownVtbl DirectMusicWaveTrack_Unknown_Vtbl = {
	IDirectMusicWaveTrack_IUnknown_QueryInterface,
	IDirectMusicWaveTrack_IUnknown_AddRef,
	IDirectMusicWaveTrack_IUnknown_Release
};

/* IDirectMusicWaveTrack IDirectMusicTrack8 part: */
static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_QueryInterface (LPDIRECTMUSICTRACK8 iface, REFIID riid, LPVOID *ppobj) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	return IUnknown_QueryInterface ((LPUNKNOWN)&This->UnknownVtbl, riid, ppobj);
}

static ULONG WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_AddRef (LPDIRECTMUSICTRACK8 iface) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	return IUnknown_AddRef ((LPUNKNOWN)&This->UnknownVtbl);
}

static ULONG WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_Release (LPDIRECTMUSICTRACK8 iface) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	return IUnknown_Release ((LPUNKNOWN)&This->UnknownVtbl);
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_Init (LPDIRECTMUSICTRACK8 iface, IDirectMusicSegment* pSegment)
{
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %p): stub\n", This, pSegment);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_InitPlay (LPDIRECTMUSICTRACK8 iface, IDirectMusicSegmentState* pSegmentState, IDirectMusicPerformance* pPerformance, void** ppStateData, DWORD dwVirtualTrack8ID, DWORD dwFlags)
{
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %p, %p, %p, %d, %d): stub\n", This, pSegmentState, pPerformance, ppStateData, dwVirtualTrack8ID, dwFlags);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_EndPlay (LPDIRECTMUSICTRACK8 iface, void* pStateData)
{
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %p): stub\n", This, pStateData);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_Play (LPDIRECTMUSICTRACK8 iface, void* pStateData, MUSIC_TIME mtStart, MUSIC_TIME mtEnd, MUSIC_TIME mtOffset, DWORD dwFlags, IDirectMusicPerformance* pPerf, IDirectMusicSegmentState* pSegSt, DWORD dwVirtualID)
{
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %p, %d, %d, %d, %d, %p, %p, %d): stub\n", This, pStateData, mtStart, mtEnd, mtOffset, dwFlags, pPerf, pSegSt, dwVirtualID);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_GetParam (LPDIRECTMUSICTRACK8 iface, REFGUID rguidType, MUSIC_TIME mtTime, MUSIC_TIME* pmtNext, void* pParam) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %s, %d, %p, %p): stub\n", This, debugstr_dmguid(rguidType), mtTime, pmtNext, pParam);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_SetParam (LPDIRECTMUSICTRACK8 iface, REFGUID rguidType, MUSIC_TIME mtTime, void* pParam) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %s, %d, %p): stub\n", This, debugstr_dmguid(rguidType), mtTime, pParam);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_IsParamSupported (LPDIRECTMUSICTRACK8 iface, REFGUID rguidType) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);

	TRACE("(%p, %s)\n", This, debugstr_dmguid(rguidType));
	if (IsEqualGUID (rguidType, &GUID_Disable_Auto_Download)
		|| IsEqualGUID (rguidType, &GUID_Download)
		|| IsEqualGUID (rguidType, &GUID_DownloadToAudioPath)
		|| IsEqualGUID (rguidType, &GUID_Enable_Auto_Download)) {
		TRACE("param supported\n");
		return S_OK;
	}
	TRACE("param unsupported\n");
	return DMUS_E_TYPE_UNSUPPORTED;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_AddNotificationType (LPDIRECTMUSICTRACK8 iface, REFGUID rguidNotificationType) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %s): stub\n", This, debugstr_dmguid(rguidNotificationType));
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_RemoveNotificationType (LPDIRECTMUSICTRACK8 iface, REFGUID rguidNotificationType) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %s): stub\n", This, debugstr_dmguid(rguidNotificationType));
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_Clone (LPDIRECTMUSICTRACK8 iface, MUSIC_TIME mtStart, MUSIC_TIME mtEnd, IDirectMusicTrack** ppTrack) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %d, %d, %p): stub\n", This, mtStart, mtEnd, ppTrack);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_PlayEx (LPDIRECTMUSICTRACK8 iface, void* pStateData, REFERENCE_TIME rtStart, REFERENCE_TIME rtEnd, REFERENCE_TIME rtOffset, DWORD dwFlags, IDirectMusicPerformance* pPerf, IDirectMusicSegmentState* pSegSt, DWORD dwVirtualID) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %p, 0x%s, 0x%s, 0x%s, %d, %p, %p, %d): stub\n", This, pStateData, wine_dbgstr_longlong(rtStart),
	    wine_dbgstr_longlong(rtEnd), wine_dbgstr_longlong(rtOffset), dwFlags, pPerf, pSegSt, dwVirtualID);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_GetParamEx (LPDIRECTMUSICTRACK8 iface, REFGUID rguidType, REFERENCE_TIME rtTime, REFERENCE_TIME* prtNext, void* pParam, void* pStateData, DWORD dwFlags) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %s, 0x%s, %p, %p, %p, %d): stub\n", This, debugstr_dmguid(rguidType),
	    wine_dbgstr_longlong(rtTime), prtNext, pParam, pStateData, dwFlags);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_SetParamEx (LPDIRECTMUSICTRACK8 iface, REFGUID rguidType, REFERENCE_TIME rtTime, void* pParam, void* pStateData, DWORD dwFlags) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %s, 0x%s, %p, %p, %d): stub\n", This, debugstr_dmguid(rguidType),
	    wine_dbgstr_longlong(rtTime), pParam, pStateData, dwFlags);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_Compose (LPDIRECTMUSICTRACK8 iface, IUnknown* pContext, DWORD dwTrackGroup, IDirectMusicTrack** ppResultTrack) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %p, %d, %p): stub\n", This, pContext, dwTrackGroup, ppResultTrack);
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IDirectMusicTrack_Join (LPDIRECTMUSICTRACK8 iface, IDirectMusicTrack* pNewTrack, MUSIC_TIME mtJoin, IUnknown* pContext, DWORD dwTrackGroup, IDirectMusicTrack** ppResultTrack) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, TrackVtbl, iface);
	FIXME("(%p, %p, %d, %p, %d, %p): stub\n", This, pNewTrack, mtJoin, pContext, dwTrackGroup, ppResultTrack);
	return S_OK;
}

static const IDirectMusicTrack8Vtbl DirectMusicWaveTrack_Track_Vtbl = {
	IDirectMusicWaveTrack_IDirectMusicTrack_QueryInterface,
	IDirectMusicWaveTrack_IDirectMusicTrack_AddRef,
	IDirectMusicWaveTrack_IDirectMusicTrack_Release,
	IDirectMusicWaveTrack_IDirectMusicTrack_Init,
	IDirectMusicWaveTrack_IDirectMusicTrack_InitPlay,
	IDirectMusicWaveTrack_IDirectMusicTrack_EndPlay,
	IDirectMusicWaveTrack_IDirectMusicTrack_Play,
	IDirectMusicWaveTrack_IDirectMusicTrack_GetParam,
	IDirectMusicWaveTrack_IDirectMusicTrack_SetParam,
	IDirectMusicWaveTrack_IDirectMusicTrack_IsParamSupported,
	IDirectMusicWaveTrack_IDirectMusicTrack_AddNotificationType,
	IDirectMusicWaveTrack_IDirectMusicTrack_RemoveNotificationType,
	IDirectMusicWaveTrack_IDirectMusicTrack_Clone,
	IDirectMusicWaveTrack_IDirectMusicTrack_PlayEx,
	IDirectMusicWaveTrack_IDirectMusicTrack_GetParamEx,
	IDirectMusicWaveTrack_IDirectMusicTrack_SetParamEx,
	IDirectMusicWaveTrack_IDirectMusicTrack_Compose,
	IDirectMusicWaveTrack_IDirectMusicTrack_Join
};

/* IDirectMusicWaveTrack IPersistStream part: */
static HRESULT WINAPI IDirectMusicWaveTrack_IPersistStream_QueryInterface (LPPERSISTSTREAM iface, REFIID riid, LPVOID *ppobj) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, PersistStreamVtbl, iface);
	return IUnknown_QueryInterface ((LPUNKNOWN)&This->UnknownVtbl, riid, ppobj);
}

static ULONG WINAPI IDirectMusicWaveTrack_IPersistStream_AddRef (LPPERSISTSTREAM iface) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, PersistStreamVtbl, iface);
	return IUnknown_AddRef ((LPUNKNOWN)&This->UnknownVtbl);
}

static ULONG WINAPI IDirectMusicWaveTrack_IPersistStream_Release (LPPERSISTSTREAM iface) {
	ICOM_THIS_MULTI(IDirectMusicWaveTrack, PersistStreamVtbl, iface);
	return IUnknown_Release ((LPUNKNOWN)&This->UnknownVtbl);
}

static HRESULT WINAPI IDirectMusicWaveTrack_IPersistStream_GetClassID (LPPERSISTSTREAM iface, CLSID* pClassID) {
	return E_NOTIMPL;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IPersistStream_IsDirty (LPPERSISTSTREAM iface) {
	return E_NOTIMPL;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IPersistStream_Load (LPPERSISTSTREAM iface, IStream* pStm) {
	FIXME(": Loading not implemented yet\n");
	return S_OK;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IPersistStream_Save (LPPERSISTSTREAM iface, IStream* pStm, BOOL fClearDirty) {
	return E_NOTIMPL;
}

static HRESULT WINAPI IDirectMusicWaveTrack_IPersistStream_GetSizeMax (LPPERSISTSTREAM iface, ULARGE_INTEGER* pcbSize) {
	return E_NOTIMPL;
}

static const IPersistStreamVtbl DirectMusicWaveTrack_PersistStream_Vtbl = {
	IDirectMusicWaveTrack_IPersistStream_QueryInterface,
	IDirectMusicWaveTrack_IPersistStream_AddRef,
	IDirectMusicWaveTrack_IPersistStream_Release,
	IDirectMusicWaveTrack_IPersistStream_GetClassID,
	IDirectMusicWaveTrack_IPersistStream_IsDirty,
	IDirectMusicWaveTrack_IPersistStream_Load,
	IDirectMusicWaveTrack_IPersistStream_Save,
	IDirectMusicWaveTrack_IPersistStream_GetSizeMax
};

/* for ClassFactory */
HRESULT WINAPI create_dmwavetrack(REFIID lpcGUID, void **ppobj)
{
	IDirectMusicWaveTrack* track;
	
	track = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDirectMusicWaveTrack));
	if (NULL == track) {
		*ppobj = NULL;
		return E_OUTOFMEMORY;
	}
	track->UnknownVtbl = &DirectMusicWaveTrack_Unknown_Vtbl;
	track->TrackVtbl = &DirectMusicWaveTrack_Track_Vtbl;
	track->PersistStreamVtbl = &DirectMusicWaveTrack_PersistStream_Vtbl;
	track->pDesc = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DMUS_OBJECTDESC));
	DM_STRUCT_INIT(track->pDesc);
	track->pDesc->dwValidData |= DMUS_OBJ_CLASS;
	track->pDesc->guidClass = CLSID_DirectMusicWaveTrack;
	track->ref = 0; /* will be inited by QueryInterface */

	return IDirectMusicWaveTrack_IUnknown_QueryInterface ((LPUNKNOWN)&track->UnknownVtbl, lpcGUID, ppobj);
}
