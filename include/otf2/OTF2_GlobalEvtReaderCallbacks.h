/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2012,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2012,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2012,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2012,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2012,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2012,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2012,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */


#ifndef OTF2_GLOBAL_EVT_READER_CALLBACKS_H
#define OTF2_GLOBAL_EVT_READER_CALLBACKS_H


/**
 *  @file
 *  @source     templates/OTF2_GlobalEvtReaderCallbacks.tmpl.h
 *
 *  @brief      This defines the callbacks for the global event reader.
 */


#include <stdint.h>


#include <otf2/OTF2_ErrorCodes.h>


#include <otf2/OTF2_GeneralDefinitions.h>
#include <otf2/OTF2_AttributeList.h>
#include <otf2/OTF2_Events.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @brief Opaque struct which holds all event record callbacks.
 */
typedef struct OTF2_GlobalEvtReaderCallbacks_struct OTF2_GlobalEvtReaderCallbacks;


/** @brief Allocates a new struct for the event callbacks.
 *
 *  @return A newly allocated struct of type @eref{OTF2_GlobalEvtReaderCallbacks}.
 */
OTF2_GlobalEvtReaderCallbacks*
OTF2_GlobalEvtReaderCallbacks_New( void );


/** @brief Deallocates a struct for the global event callbacks.
 *
 *  @param globalEvtReaderCallbacks Handle to a struct previously allocated
 *                                  with @eref{OTF2_GlobalEvtReaderCallbacks_New}.
 */
void
OTF2_GlobalEvtReaderCallbacks_Delete( OTF2_GlobalEvtReaderCallbacks* globalEvtReaderCallbacks );


/** @brief Clears a struct for the global event callbacks.
 *
 *  @param globalEvtReaderCallbacks Handle to a struct previously allocated
 *                                  with @eref{OTF2_GlobalEvtReaderCallbacks_New}.
 */
void
OTF2_GlobalEvtReaderCallbacks_Clear( OTF2_GlobalEvtReaderCallbacks* globalEvtReaderCallbacks );


/** @brief Callback for an unknown event record.
 *
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_Unknown )( OTF2_LocationRef    locationID,
                                           OTF2_TimeStamp      time,
                                           void*               userData,
                                           OTF2_AttributeList* attributeList );


/** @brief Registers the callback for unknown events.
 *
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param unknownCallback          Function which should be called for all
 *                                  unknown events.
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetUnknownCallback(
    OTF2_GlobalEvtReaderCallbacks*       globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_Unknown unknownCallback );


/** @brief Callback for the BufferFlush event record.
 *
 *  This event signals that the internal buffer was flushed at the given
 *  time.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param stopTime      The time the buffer flush finished.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_BufferFlush )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_TimeStamp stopTime );


/** @brief Registers the callback for the BufferFlush event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param bufferFlushCallback      Function which should be called for all
 *                                  @eref{BufferFlush} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetBufferFlushCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_BufferFlush bufferFlushCallback );


/** @brief Callback for the MeasurementOnOff event record.
 *
 *  This event signals where the measurement system turned measurement on
 *  or off.
 *  
 *  @param locationID      The location where this event happened.
 *  @param time            The time when this event happened.
 *  @param userData        User data as set by
 *                         @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                         @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList   Additional attributes for this event.
 *  @param measurementMode Is the measurement turned on
 *                         (@eref{OTF2_MEASUREMENT_ON}) or off
 *                         (@eref{OTF2_MEASUREMENT_OFF})?
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MeasurementOnOff )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_MeasurementMode measurementMode );


/** @brief Registers the callback for the MeasurementOnOff event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param measurementOnOffCallback Function which should be called for all
 *                                  @eref{MeasurementOnOff} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMeasurementOnOffCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MeasurementOnOff measurementOnOffCallback );


/** @brief Callback for the Enter event record.
 *
 *  An enter record indicates that the program enters a code region.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_Enter )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


/** @brief Registers the callback for the Enter event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param enterCallback            Function which should be called for all
 *                                  @eref{Enter} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetEnterCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_Enter enterCallback );


/** @brief Callback for the Leave event record.
 *
 *  An enter record indicates that the program leaves a code region.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_Leave )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


/** @brief Registers the callback for the Leave event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param leaveCallback            Function which should be called for all
 *                                  @eref{Leave} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetLeaveCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_Leave leaveCallback );


/** @brief Callback for the MpiSend event record.
 *
 *  A MpiSend record indicates that a MPI message send process was
 *  initiated (MPI_SEND). It keeps the necessary information for this
 *  event: receiver of the message, communicator, and the message tag.
 *  You can optionally add further information like the message length
 *  (size of the send buffer).
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param receiver      MPI rank of receiver in @p communicator.
 *  @param communicator  Communicator ID. References a @eref{Comm} definition and
 *                       will be mapped to the global definition if a mapping
 *                       table of type @eref{OTF2_MAPPING_COMM} is available.
 *  @param msgTag        Message tag
 *  @param msgLength     Message length
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiSend )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength );


/** @brief Registers the callback for the MpiSend event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param mpiSendCallback          Function which should be called for all
 *                                  @eref{MpiSend} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiSendCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiSend mpiSendCallback );


/** @brief Callback for the MpiIsend event record.
 *
 *  A MpiIsend record indicates that a MPI message send process was
 *  initiated (MPI_ISEND). It keeps the necessary information for this
 *  event: receiver of the message, communicator, and the message tag.
 *  You can optionally add further information like the message length
 *  (size of the send buffer).
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param receiver      MPI rank of receiver in @p communicator.
 *  @param communicator  Communicator ID. References a @eref{Comm} definition and
 *                       will be mapped to the global definition if a mapping
 *                       table of type @eref{OTF2_MAPPING_COMM} is available.
 *  @param msgTag        Message tag
 *  @param msgLength     Message length
 *  @param requestID     ID of the related request
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiIsend )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint32_t receiver,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID );


/** @brief Registers the callback for the MpiIsend event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param mpiIsendCallback         Function which should be called for all
 *                                  @eref{MpiIsend} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiIsendCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiIsend mpiIsendCallback );


/** @brief Callback for the MpiIsendComplete event record.
 *
 *  Signals the completion of non-blocking send request.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param requestID     ID of the related request
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiIsendComplete )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint64_t requestID );


/** @brief Registers the callback for the MpiIsendComplete event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param mpiIsendCompleteCallback Function which should be called for all
 *                                  @eref{MpiIsendComplete} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiIsendCompleteCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiIsendComplete mpiIsendCompleteCallback );


/** @brief Callback for the MpiIrecvRequest event record.
 *
 *  Signals the request of a receive, which can be completed later.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param requestID     ID of the requested receive
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiIrecvRequest )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint64_t requestID );


/** @brief Registers the callback for the MpiIrecvRequest event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param mpiIrecvRequestCallback  Function which should be called for all
 *                                  @eref{MpiIrecvRequest} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiIrecvRequestCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiIrecvRequest mpiIrecvRequestCallback );


/** @brief Callback for the MpiRecv event record.
 *
 *  A MpiRecv record indicates that a MPI message was received (MPI_RECV).
 *  It keeps the necessary information for this event: sender of the
 *  message, communicator, and the message tag. You can optionally add
 *  further information like the message length (size of the receive
 *  buffer).
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param sender        MPI rank of sender in @p communicator.
 *  @param communicator  Communicator ID. References a @eref{Comm} definition and
 *                       will be mapped to the global definition if a mapping
 *                       table of type @eref{OTF2_MAPPING_COMM} is available.
 *  @param msgTag        Message tag
 *  @param msgLength     Message length
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiRecv )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength );


/** @brief Registers the callback for the MpiRecv event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param mpiRecvCallback          Function which should be called for all
 *                                  @eref{MpiRecv} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiRecvCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiRecv mpiRecvCallback );


/** @brief Callback for the MpiIrecv event record.
 *
 *  A MpiIrecv record indicates that a MPI message was received
 *  (MPI_IRECV). It keeps the necessary information for this event:
 *  sender of the message, communicator, and the message tag. You can
 *  optionally add further information like the message length (size
 *  of the receive buffer).
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param sender        MPI rank of sender in @p communicator.
 *  @param communicator  Communicator ID. References a @eref{Comm} definition and
 *                       will be mapped to the global definition if a mapping
 *                       table of type @eref{OTF2_MAPPING_COMM} is available.
 *  @param msgTag        Message tag
 *  @param msgLength     Message length
 *  @param requestID     ID of the related request
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiIrecv )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint32_t sender,
OTF2_CommRef communicator,
uint32_t msgTag,
uint64_t msgLength,
uint64_t requestID );


/** @brief Registers the callback for the MpiIrecv event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param mpiIrecvCallback         Function which should be called for all
 *                                  @eref{MpiIrecv} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiIrecvCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiIrecv mpiIrecvCallback );


/** @brief Callback for the MpiRequestTest event record.
 *
 *  This events appears if the program tests if a request has already
 *  completed but the test failed.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param requestID     ID of the related request
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiRequestTest )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint64_t requestID );


/** @brief Registers the callback for the MpiRequestTest event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param mpiRequestTestCallback   Function which should be called for all
 *                                  @eref{MpiRequestTest} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiRequestTestCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiRequestTest mpiRequestTestCallback );


/** @brief Callback for the MpiRequestCancelled event record.
 *
 *  This events appears if the program canceled a request.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param requestID     ID of the related request
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiRequestCancelled )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint64_t requestID );


/** @brief Registers the callback for the MpiRequestCancelled event.
 *  
 *  @param globalEvtReaderCallbacks    Struct for all callbacks.
 *  @param mpiRequestCancelledCallback Function which should be called for all
 *                                     @eref{MpiRequestCancelled}
 *                                     definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiRequestCancelledCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiRequestCancelled mpiRequestCancelledCallback );


/** @brief Callback for the MpiCollectiveBegin event record.
 *
 *  A MpiCollectiveBegin record marks the begin of a MPI collective
 *  operation (MPI_GATHER, MPI_SCATTER etc.).
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiCollectiveBegin )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList );


/** @brief Registers the callback for the MpiCollectiveBegin event.
 *  
 *  @param globalEvtReaderCallbacks   Struct for all callbacks.
 *  @param mpiCollectiveBeginCallback Function which should be called for all
 *                                    @eref{MpiCollectiveBegin} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiCollectiveBeginCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiCollectiveBegin mpiCollectiveBeginCallback );


/** @brief Callback for the MpiCollectiveEnd event record.
 *
 *  A MpiCollectiveEnd record marks the end of a MPI collective operation
 *  (MPI_GATHER, MPI_SCATTER etc.). It keeps the necessary information
 *  for this event: type of collective operation, communicator, the
 *  root of this collective operation. You can optionally add further
 *  information like sent and received bytes.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param collectiveOp  Determines which collective operation it is.
 *  @param communicator  Communicator References a @eref{Comm} definition and
 *                       will be mapped to the global definition if a mapping
 *                       table of type @eref{OTF2_MAPPING_COMM} is available.
 *  @param root          MPI rank of root in @p communicator.
 *  @param sizeSent      Size of the sent message.
 *  @param sizeReceived  Size of the received message.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_MpiCollectiveEnd )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CollectiveOp collectiveOp,
OTF2_CommRef communicator,
uint32_t root,
uint64_t sizeSent,
uint64_t sizeReceived );


/** @brief Registers the callback for the MpiCollectiveEnd event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param mpiCollectiveEndCallback Function which should be called for all
 *                                  @eref{MpiCollectiveEnd} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiCollectiveEndCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiCollectiveEnd mpiCollectiveEndCallback );


/** @brief Callback for the OmpFork event record.
 *
 *  An OmpFork record marks that an OpenMP Thread forks a thread team.
 *  
 *  This event record is superseded by the @eref{ThreadFork} event record
 *  and should not be used when the @eref{ThreadFork} event record is
 *  in use.
 *  
 *  @param locationID               The location where this event happened.
 *  @param time                     The time when this event happened.
 *  @param userData                 User data as set by
 *                                  @eref{OTF2_Reader_RegisterGlobalEvtCallbacks}
 *                                  or
 *                                  @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList            Additional attributes for this event.
 *  @param numberOfRequestedThreads Requested size of the team.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_OmpFork )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint32_t numberOfRequestedThreads );


/** @brief Registers the callback for the OmpFork event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param ompForkCallback          Function which should be called for all
 *                                  @eref{OmpFork} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpForkCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpFork ompForkCallback );


/** @brief Callback for the OmpJoin event record.
 *
 *  An OmpJoin record marks that a team of threads is joint and only the
 *  master thread continues execution.
 *  
 *  This event record is superseded by the @eref{ThreadJoin} event record
 *  and should not be used when the @eref{ThreadJoin} event record is
 *  in use.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_OmpJoin )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList );


/** @brief Registers the callback for the OmpJoin event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param ompJoinCallback          Function which should be called for all
 *                                  @eref{OmpJoin} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpJoinCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpJoin ompJoinCallback );


/** @brief Callback for the OmpAcquireLock event record.
 *
 *  An OmpAcquireLock record marks that a thread acquires an OpenMP lock.
 *  
 *  This event record is superseded by the @eref{ThreadAcquireLock} event
 *  record and should not be used when the @eref{ThreadAcquireLock}
 *  event record is in use.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param lockID           ID of the lock.
 *  @param acquisitionOrder A monotonically increasing number to determine the
 *                          order of lock acquisitions (with unsynchronized
 *                          clocks this is otherwise not possible).
 *                          Corresponding acquire-release events have same
 *                          number.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_OmpAcquireLock )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder );


/** @brief Registers the callback for the OmpAcquireLock event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param ompAcquireLockCallback   Function which should be called for all
 *                                  @eref{OmpAcquireLock} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpAcquireLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpAcquireLock ompAcquireLockCallback );


/** @brief Callback for the OmpReleaseLock event record.
 *
 *  An OmpReleaseLock record marks that a thread releases an OpenMP lock.
 *  
 *  This event record is superseded by the @eref{ThreadReleaseLock} event
 *  record and should not be used when the @eref{ThreadReleaseLock}
 *  event record is in use.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param lockID           ID of the lock.
 *  @param acquisitionOrder A monotonically increasing number to determine the
 *                          order of lock acquisitions (with unsynchronized
 *                          clocks this is otherwise not possible).
 *                          Corresponding acquire-release events have same
 *                          number.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_OmpReleaseLock )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint32_t lockID,
uint32_t acquisitionOrder );


/** @brief Registers the callback for the OmpReleaseLock event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param ompReleaseLockCallback   Function which should be called for all
 *                                  @eref{OmpReleaseLock} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpReleaseLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpReleaseLock ompReleaseLockCallback );


/** @brief Callback for the OmpTaskCreate event record.
 *
 *  An OmpTaskCreate record marks that an OpenMP Task was/will be created
 *  in the current region.
 *  
 *  This event record is superseded by the @eref{ThreadTaskCreate} event
 *  record and should not be used when the @eref{ThreadTaskCreate}
 *  event record is in use.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param taskID        Identifier of the newly created task instance.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_OmpTaskCreate )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint64_t taskID );


/** @brief Registers the callback for the OmpTaskCreate event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param ompTaskCreateCallback    Function which should be called for all
 *                                  @eref{OmpTaskCreate} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpTaskCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpTaskCreate ompTaskCreateCallback );


/** @brief Callback for the OmpTaskSwitch event record.
 *
 *  An OmpTaskSwitch record indicates that the execution of the current
 *  task will be suspended and another task starts/restarts its
 *  execution. Please note that this may change the current call stack
 *  of the executing location.
 *  
 *  This event record is superseded by the @eref{ThreadTaskSwitch} event
 *  record and should not be used when the @eref{ThreadTaskSwitch}
 *  event record is in use.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param taskID        Identifier of the now active task instance.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_OmpTaskSwitch )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint64_t taskID );


/** @brief Registers the callback for the OmpTaskSwitch event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param ompTaskSwitchCallback    Function which should be called for all
 *                                  @eref{OmpTaskSwitch} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpTaskSwitchCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpTaskSwitch ompTaskSwitchCallback );


/** @brief Callback for the OmpTaskComplete event record.
 *
 *  An OmpTaskComplete record indicates that the execution of an OpenMP
 *  task has finished.
 *  
 *  This event record is superseded by the @eref{ThreadTaskComplete} event
 *  record and should not be used when the @eref{ThreadTaskComplete}
 *  event record is in use.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param taskID        Identifier of the completed task instance.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_OmpTaskComplete )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
uint64_t taskID );


/** @brief Registers the callback for the OmpTaskComplete event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param ompTaskCompleteCallback  Function which should be called for all
 *                                  @eref{OmpTaskComplete} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpTaskCompleteCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpTaskComplete ompTaskCompleteCallback );


/** @brief Callback for the Metric event record.
 *
 *  A metric event is always stored at the location that recorded the
 *  metric. A metric event can reference a metric class or metric
 *  instance. Therefore, metric classes and instances share same ID
 *  space. Synchronous metrics are always located right before the
 *  according enter and leave event.
 *  
 *  @param locationID      The location where this event happened.
 *  @param time            The time when this event happened.
 *  @param userData        User data as set by
 *                         @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                         @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList   Additional attributes for this event.
 *  @param metric          Could be a metric class or a metric instance.
 *                         References a @eref{MetricClass}, or a
 *                         @eref{MetricInstance} definition and will be
 *                         mapped to the global definition if a mapping table
 *                         of type @eref{OTF2_MAPPING_METRIC} is available.
 *  @param numberOfMetrics Number of metrics with in the set.
 *  @param typeIDs         List of metric types. These types must match that of
 *                         the corresponding @eref{MetricMember} definitions.
 *  @param metricValues    List of metric values.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_Metric )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_MetricRef metric,
uint8_t numberOfMetrics,
const OTF2_Type* typeIDs,
const OTF2_MetricValue* metricValues );


/** @brief Registers the callback for the Metric event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param metricCallback           Function which should be called for all
 *                                  @eref{Metric} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMetricCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_Metric metricCallback );


/** @brief Callback for the ParameterString event record.
 *
 *  A ParameterString record marks that in the current region, the
 *  specified string parameter has the specified value.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param parameter     Parameter ID. References a @eref{Parameter} definition
 *                       and will be mapped to the global definition if a
 *                       mapping table of type @eref{OTF2_MAPPING_PARAMETER}
 *                       is available.
 *  @param string        Value: Handle of a string definition References a
 *                       @eref{String} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_STRING} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ParameterString )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
OTF2_StringRef string );


/** @brief Registers the callback for the ParameterString event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param parameterStringCallback  Function which should be called for all
 *                                  @eref{ParameterString} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetParameterStringCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ParameterString parameterStringCallback );


/** @brief Callback for the ParameterInt event record.
 *
 *  A ParameterInt record marks that in the current region, the specified
 *  integer parameter has the specified value.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param parameter     Parameter ID. References a @eref{Parameter} definition
 *                       and will be mapped to the global definition if a
 *                       mapping table of type @eref{OTF2_MAPPING_PARAMETER}
 *                       is available.
 *  @param value         Value of the recorded parameter.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ParameterInt )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
int64_t value );


/** @brief Registers the callback for the ParameterInt event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param parameterIntCallback     Function which should be called for all
 *                                  @eref{ParameterInt} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetParameterIntCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ParameterInt parameterIntCallback );


/** @brief Callback for the ParameterUnsignedInt event record.
 *
 *  A ParameterUnsignedInt record marks that in the current region, the
 *  specified unsigned integer parameter has the specified value.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param parameter     Parameter ID. References a @eref{Parameter} definition
 *                       and will be mapped to the global definition if a
 *                       mapping table of type @eref{OTF2_MAPPING_PARAMETER}
 *                       is available.
 *  @param value         Value of the recorded parameter.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ParameterUnsignedInt )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_ParameterRef parameter,
uint64_t value );


/** @brief Registers the callback for the ParameterUnsignedInt event.
 *  
 *  @param globalEvtReaderCallbacks     Struct for all callbacks.
 *  @param parameterUnsignedIntCallback Function which should be called for all
 *                                      @eref{ParameterUnsignedInt}
 *                                      definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetParameterUnsignedIntCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ParameterUnsignedInt parameterUnsignedIntCallback );


/** @brief Callback for the RmaWinCreate event record.
 *
 *  A RmaWinCreate record denotes the creation of a RMA window.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window created. References a @eref{RmaWin}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaWinCreate )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


/** @brief Registers the callback for the RmaWinCreate event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaWinCreateCallback     Function which should be called for all
 *                                  @eref{RmaWinCreate} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaWinCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaWinCreate rmaWinCreateCallback );


/** @brief Callback for the RmaWinDestroy event record.
 *
 *  A RmaWinDestroy record denotes the destruction of a RMA window.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window destructed. References a @eref{RmaWin}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaWinDestroy )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


/** @brief Registers the callback for the RmaWinDestroy event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaWinDestroyCallback    Function which should be called for all
 *                                  @eref{RmaWinDestroy} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaWinDestroyCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaWinDestroy rmaWinDestroyCallback );


/** @brief Callback for the RmaCollectiveBegin event record.
 *
 *  A RmaCollectiveBegin record denotes the beginning of a collective RMA
 *  operation.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaCollectiveBegin )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList );


/** @brief Registers the callback for the RmaCollectiveBegin event.
 *  
 *  @param globalEvtReaderCallbacks   Struct for all callbacks.
 *  @param rmaCollectiveBeginCallback Function which should be called for all
 *                                    @eref{RmaCollectiveBegin} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaCollectiveBeginCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaCollectiveBegin rmaCollectiveBeginCallback );


/** @brief Callback for the RmaCollectiveEnd event record.
 *
 *  A RmaCollectiveEnd record denotes the end of a collective RMA
 *  operation.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param collectiveOp  Determines which collective operation it is.
 *  @param syncLevel     Synchronization level of this collective operation.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param root          Root process for this operation.
 *  @param bytesSent     Bytes sent in operation.
 *  @param bytesReceived Bytes receives in operation.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaCollectiveEnd )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CollectiveOp collectiveOp,
OTF2_RmaSyncLevel syncLevel,
OTF2_RmaWinRef win,
uint32_t root,
uint64_t bytesSent,
uint64_t bytesReceived );


/** @brief Registers the callback for the RmaCollectiveEnd event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaCollectiveEndCallback Function which should be called for all
 *                                  @eref{RmaCollectiveEnd} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaCollectiveEndCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaCollectiveEnd rmaCollectiveEndCallback );


/** @brief Callback for the RmaGroupSync event record.
 *
 *  A RmaGroupSync record denotes the synchronization with a subgroup of
 *  processes on a window.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param syncLevel     Synchronization level of this collective operation.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param group         Group of remote processes involved in synchronization.
 *                       References a @eref{Group} definition and will be
 *                       mapped to the global definition if a mapping table
 *                       of type @eref{OTF2_MAPPING_GROUP} is available.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaGroupSync )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaSyncLevel syncLevel,
OTF2_RmaWinRef win,
OTF2_GroupRef group );


/** @brief Registers the callback for the RmaGroupSync event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaGroupSyncCallback     Function which should be called for all
 *                                  @eref{RmaGroupSync} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaGroupSyncCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaGroupSync rmaGroupSyncCallback );


/** @brief Callback for the RmaRequestLock event record.
 *
 *  A RmaRequestLock record denotes the time a lock was requested and with
 *  it the earliest time it could have been granted.  It is used to
 *  mark (possibly) non-blocking lock request, as defined by the MPI
 *  standard.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param remote        Rank of the locked remote process.
 *  @param lockId        ID of the lock acquired, if multiple locks are defined
 *                       on a window.
 *  @param lockType      Type of lock acquired.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaRequestLock )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


/** @brief Registers the callback for the RmaRequestLock event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaRequestLockCallback   Function which should be called for all
 *                                  @eref{RmaRequestLock} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaRequestLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaRequestLock rmaRequestLockCallback );


/** @brief Callback for the RmaAcquireLock event record.
 *
 *  A RmaAcquireLock record denotes the time a lock was acquired by the
 *  process.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param remote        Rank of the locked remote process.
 *  @param lockId        ID of the lock acquired, if multiple locks are defined
 *                       on a window.
 *  @param lockType      Type of lock acquired.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaAcquireLock )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


/** @brief Registers the callback for the RmaAcquireLock event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaAcquireLockCallback   Function which should be called for all
 *                                  @eref{RmaAcquireLock} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaAcquireLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaAcquireLock rmaAcquireLockCallback );


/** @brief Callback for the RmaTryLock event record.
 *
 *  A RmaTryLock record denotes the time of an unsuccessful attempt to
 *  acquire the lock.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param remote        Rank of the locked remote process.
 *  @param lockId        ID of the lock acquired, if multiple locks are defined
 *                       on a window.
 *  @param lockType      Type of lock acquired.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaTryLock )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId,
OTF2_LockType lockType );


/** @brief Registers the callback for the RmaTryLock event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaTryLockCallback       Function which should be called for all
 *                                  @eref{RmaTryLock} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaTryLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaTryLock rmaTryLockCallback );


/** @brief Callback for the RmaReleaseLock event record.
 *
 *  A RmaReleaseLock record denotes the time the lock was released.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param remote        Rank of the locked remote process.
 *  @param lockId        ID of the lock released, if multiple locks are defined
 *                       on a window.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaReleaseLock )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t lockId );


/** @brief Registers the callback for the RmaReleaseLock event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaReleaseLockCallback   Function which should be called for all
 *                                  @eref{RmaReleaseLock} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaReleaseLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaReleaseLock rmaReleaseLockCallback );


/** @brief Callback for the RmaSync event record.
 *
 *  A RmaSync record denotes the direct synchronization with a possibly
 *  remote process.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param remote        Rank of the locked remote process.
 *  @param syncType      Type of synchronization.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaSync )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
OTF2_RmaSyncType syncType );


/** @brief Registers the callback for the RmaSync event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaSyncCallback          Function which should be called for all
 *                                  @eref{RmaSync} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaSyncCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaSync rmaSyncCallback );


/** @brief Callback for the RmaWaitChange event record.
 *
 *  A RmaWaitChange record denotes the change of a window that was waited
 *  for.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaWaitChange )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win );


/** @brief Registers the callback for the RmaWaitChange event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaWaitChangeCallback    Function which should be called for all
 *                                  @eref{RmaWaitChange} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaWaitChangeCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaWaitChange rmaWaitChangeCallback );


/** @brief Callback for the RmaPut event record.
 *
 *  A RmaPut record denotes the time a put operation was issued.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param remote        Rank of the target process.
 *  @param bytes         Bytes sent to target.
 *  @param matchingId    ID used for matching the corresponding completion
 *                       record.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaPut )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId );


/** @brief Registers the callback for the RmaPut event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaPutCallback           Function which should be called for all
 *                                  @eref{RmaPut} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaPutCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaPut rmaPutCallback );


/** @brief Callback for the RmaGet event record.
 *
 *  A RmaGet record denotes the time a get operation was issued.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param remote        Rank of the target process.
 *  @param bytes         Bytes received from target.
 *  @param matchingId    ID used for matching the corresponding completion
 *                       record.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaGet )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
uint64_t bytes,
uint64_t matchingId );


/** @brief Registers the callback for the RmaGet event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaGetCallback           Function which should be called for all
 *                                  @eref{RmaGet} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaGetCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaGet rmaGetCallback );


/** @brief Callback for the RmaAtomic event record.
 *
 *  A RmaAtomic record denotes the time a atomic operation was issued.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param remote        Rank of the target process.
 *  @param type          Type of atomic operation.
 *  @param bytesSent     Bytes sent to target.
 *  @param bytesReceived Bytes received from target.
 *  @param matchingId    ID used for matching the corresponding completion
 *                       record.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaAtomic )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint32_t remote,
OTF2_RmaAtomicType type,
uint64_t bytesSent,
uint64_t bytesReceived,
uint64_t matchingId );


/** @brief Registers the callback for the RmaAtomic event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaAtomicCallback        Function which should be called for all
 *                                  @eref{RmaAtomic} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaAtomicCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaAtomic rmaAtomicCallback );


/** @brief Callback for the RmaOpCompleteBlocking event record.
 *
 *  A RmaOpCompleteBlocking record denotes the local completion of a
 *  blocking RMA operation.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param matchingId    ID used for matching the corresponding RMA operation
 *                       record.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaOpCompleteBlocking )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


/** @brief Registers the callback for the RmaOpCompleteBlocking event.
 *  
 *  @param globalEvtReaderCallbacks      Struct for all callbacks.
 *  @param rmaOpCompleteBlockingCallback Function which should be called for all
 *                                       @eref{RmaOpCompleteBlocking}
 *                                       definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteBlockingCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaOpCompleteBlocking rmaOpCompleteBlockingCallback );


/** @brief Callback for the RmaOpCompleteNonBlocking event record.
 *
 *  A RmaOpCompleteNonBlocking record denotes the local completion of a
 *  non-blocking RMA operation.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param matchingId    ID used for matching the corresponding RMA operation
 *                       record.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaOpCompleteNonBlocking )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


/** @brief Registers the callback for the RmaOpCompleteNonBlocking event.
 *  
 *  @param globalEvtReaderCallbacks         Struct for all callbacks.
 *  @param rmaOpCompleteNonBlockingCallback Function which should be called for
 *                                          all
 *                                          @eref{RmaOpCompleteNonBlocking}
 *                                          definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteNonBlockingCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaOpCompleteNonBlocking rmaOpCompleteNonBlockingCallback );


/** @brief Callback for the RmaOpTest event record.
 *
 *  A RmaOpTest record denotes that a non-blocking RMA operation has been
 *  tested for completion unsuccessfully.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param matchingId    ID used for matching the corresponding RMA operation
 *                       record.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaOpTest )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


/** @brief Registers the callback for the RmaOpTest event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param rmaOpTestCallback        Function which should be called for all
 *                                  @eref{RmaOpTest} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaOpTestCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaOpTest rmaOpTestCallback );


/** @brief Callback for the RmaOpCompleteRemote event record.
 *
 *  A RmaOpCompleteRemote record denotes the remote completion of a RMA
 *  operation.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param win           ID of the window used for this operation. References a
 *                       @eref{RmaWin} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_RMA_WIN} is available.
 *  @param matchingId    ID used for matching the corresponding RMA operation
 *                       record.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_RmaOpCompleteRemote )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RmaWinRef win,
uint64_t matchingId );


/** @brief Registers the callback for the RmaOpCompleteRemote event.
 *  
 *  @param globalEvtReaderCallbacks    Struct for all callbacks.
 *  @param rmaOpCompleteRemoteCallback Function which should be called for all
 *                                     @eref{RmaOpCompleteRemote}
 *                                     definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteRemoteCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaOpCompleteRemote rmaOpCompleteRemoteCallback );


/** @brief Callback for the ThreadFork event record.
 *
 *  A ThreadFork record marks that a thread forks a thread team.
 *  
 *  @param locationID               The location where this event happened.
 *  @param time                     The time when this event happened.
 *  @param userData                 User data as set by
 *                                  @eref{OTF2_Reader_RegisterGlobalEvtCallbacks}
 *                                  or
 *                                  @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList            Additional attributes for this event.
 *  @param model                    The threading paradigm this event took place.
 *  @param numberOfRequestedThreads Requested size of the team.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadFork )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t numberOfRequestedThreads );


/** @brief Registers the callback for the ThreadFork event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadForkCallback       Function which should be called for all
 *                                  @eref{ThreadFork} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadForkCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadFork threadForkCallback );


/** @brief Callback for the ThreadJoin event record.
 *
 *  A ThreadJoin record marks that a team of threads is joint and only the
 *  master thread continues execution.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param model         The threading paradigm this event took place.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadJoin )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_Paradigm model );


/** @brief Registers the callback for the ThreadJoin event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadJoinCallback       Function which should be called for all
 *                                  @eref{ThreadJoin} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadJoinCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadJoin threadJoinCallback );


/** @brief Callback for the ThreadTeamBegin event record.
 *
 *  The current location enters the specified thread team.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param threadTeam    Thread team References a @eref{Comm} definition and will
 *                       be mapped to the global definition if a mapping
 *                       table of type @eref{OTF2_MAPPING_COMM} is available.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadTeamBegin )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam );


/** @brief Registers the callback for the ThreadTeamBegin event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadTeamBeginCallback  Function which should be called for all
 *                                  @eref{ThreadTeamBegin} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTeamBeginCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTeamBegin threadTeamBeginCallback );


/** @brief Callback for the ThreadTeamEnd event record.
 *
 *  The current location leaves the specified thread team.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param threadTeam    Thread team References a @eref{Comm} definition and will
 *                       be mapped to the global definition if a mapping
 *                       table of type @eref{OTF2_MAPPING_COMM} is available.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadTeamEnd )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam );


/** @brief Registers the callback for the ThreadTeamEnd event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadTeamEndCallback    Function which should be called for all
 *                                  @eref{ThreadTeamEnd} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTeamEndCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTeamEnd threadTeamEndCallback );


/** @brief Callback for the ThreadAcquireLock event record.
 *
 *  A ThreadAcquireLock record marks that a thread acquires a lock.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param model            The threading paradigm this event took place.
 *  @param lockID           ID of the lock.
 *  @param acquisitionOrder A monotonically increasing number to determine the
 *                          order of lock acquisitions (with unsynchronized
 *                          clocks this is otherwise not possible).
 *                          Corresponding acquire-release events have same
 *                          number.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadAcquireLock )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder );


/** @brief Registers the callback for the ThreadAcquireLock event.
 *  
 *  @param globalEvtReaderCallbacks  Struct for all callbacks.
 *  @param threadAcquireLockCallback Function which should be called for all
 *                                   @eref{ThreadAcquireLock} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadAcquireLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadAcquireLock threadAcquireLockCallback );


/** @brief Callback for the ThreadReleaseLock event record.
 *
 *  A ThreadReleaseLock record marks that a thread releases a lock.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param model            The threading paradigm this event took place.
 *  @param lockID           ID of the lock.
 *  @param acquisitionOrder A monotonically increasing number to determine the
 *                          order of lock acquisitions (with unsynchronized
 *                          clocks this is otherwise not possible).
 *                          Corresponding acquire-release events have same
 *                          number.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadReleaseLock )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_Paradigm model,
uint32_t lockID,
uint32_t acquisitionOrder );


/** @brief Registers the callback for the ThreadReleaseLock event.
 *  
 *  @param globalEvtReaderCallbacks  Struct for all callbacks.
 *  @param threadReleaseLockCallback Function which should be called for all
 *                                   @eref{ThreadReleaseLock} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadReleaseLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadReleaseLock threadReleaseLockCallback );


/** @brief Callback for the ThreadTaskCreate event record.
 *
 *  A ThreadTaskCreate record marks that a task in was/will be created and
 *  will be processed by the specified thread team.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param threadTeam       Thread team References a @eref{Comm} definition and
 *                          will be mapped to the global definition if a
 *                          mapping table of type @eref{OTF2_MAPPING_COMM} is
 *                          available.
 *  @param creatingThread   Creating thread of this task.
 *  @param generationNumber Thread-private generation number of task's creating
 *                          thread.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadTaskCreate )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


/** @brief Registers the callback for the ThreadTaskCreate event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadTaskCreateCallback Function which should be called for all
 *                                  @eref{ThreadTaskCreate} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTaskCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTaskCreate threadTaskCreateCallback );


/** @brief Callback for the ThreadTaskSwitch event record.
 *
 *  A ThreadTaskSwitch record indicates that the execution of the current
 *  task will be suspended and another task starts/restarts its
 *  execution. Please note that this may change the current call stack
 *  of the executing location.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param threadTeam       Thread team References a @eref{Comm} definition and
 *                          will be mapped to the global definition if a
 *                          mapping table of type @eref{OTF2_MAPPING_COMM} is
 *                          available.
 *  @param creatingThread   Creating thread of this task.
 *  @param generationNumber Thread-private generation number of task's creating
 *                          thread.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadTaskSwitch )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


/** @brief Registers the callback for the ThreadTaskSwitch event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadTaskSwitchCallback Function which should be called for all
 *                                  @eref{ThreadTaskSwitch} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTaskSwitchCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTaskSwitch threadTaskSwitchCallback );


/** @brief Callback for the ThreadTaskComplete event record.
 *
 *  A ThreadTaskComplete record indicates that the execution of an OpenMP
 *  task has finished.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param threadTeam       Thread team References a @eref{Comm} definition and
 *                          will be mapped to the global definition if a
 *                          mapping table of type @eref{OTF2_MAPPING_COMM} is
 *                          available.
 *  @param creatingThread   Creating thread of this task.
 *  @param generationNumber Thread-private generation number of task's creating
 *                          thread.
 *
 *  @since Version 1.2
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadTaskComplete )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadTeam,
uint32_t creatingThread,
uint32_t generationNumber );


/** @brief Registers the callback for the ThreadTaskComplete event.
 *  
 *  @param globalEvtReaderCallbacks   Struct for all callbacks.
 *  @param threadTaskCompleteCallback Function which should be called for all
 *                                    @eref{ThreadTaskComplete} definitions.
 *
 *  @since Version 1.2
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTaskCompleteCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTaskComplete threadTaskCompleteCallback );


/** @brief Callback for the ThreadCreate event record.
 *
 *  The location created successfully a new thread.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param threadContingent The thread contingent. References a @eref{Comm}
 *                          definition and will be mapped to the global
 *                          definition if a mapping table of type
 *                          @eref{OTF2_MAPPING_COMM} is available.
 *  @param sequenceCount    A @p threadContingent unique number. The
 *                          corresponding @eref{ThreadBegin} event does have
 *                          the same number.
 *
 *  @since Version 1.3
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadCreate )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


/** @brief Registers the callback for the ThreadCreate event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadCreateCallback     Function which should be called for all
 *                                  @eref{ThreadCreate} definitions.
 *
 *  @since Version 1.3
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadCreate threadCreateCallback );


/** @brief Callback for the ThreadBegin event record.
 *
 *  Marks the begin of a thread created by another thread.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param threadContingent The thread contingent. References a @eref{Comm}
 *                          definition and will be mapped to the global
 *                          definition if a mapping table of type
 *                          @eref{OTF2_MAPPING_COMM} is available.
 *  @param sequenceCount    A @p threadContingent unique number. The
 *                          corresponding @eref{ThreadCreate} event does have
 *                          the same number.
 *
 *  @since Version 1.3
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadBegin )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


/** @brief Registers the callback for the ThreadBegin event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadBeginCallback      Function which should be called for all
 *                                  @eref{ThreadBegin} definitions.
 *
 *  @since Version 1.3
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadBeginCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadBegin threadBeginCallback );


/** @brief Callback for the ThreadWait event record.
 *
 *  The location waits for the completion of another thread.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param threadContingent The thread contingent. References a @eref{Comm}
 *                          definition and will be mapped to the global
 *                          definition if a mapping table of type
 *                          @eref{OTF2_MAPPING_COMM} is available.
 *  @param sequenceCount    A @p threadContingent unique number. The
 *                          corresponding @eref{ThreadEnd} event does have
 *                          the same number.
 *
 *  @since Version 1.3
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadWait )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


/** @brief Registers the callback for the ThreadWait event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadWaitCallback       Function which should be called for all
 *                                  @eref{ThreadWait} definitions.
 *
 *  @since Version 1.3
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadWaitCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadWait threadWaitCallback );


/** @brief Callback for the ThreadEnd event record.
 *
 *  Marks the end of a thread.
 *  
 *  @param locationID       The location where this event happened.
 *  @param time             The time when this event happened.
 *  @param userData         User data as set by
 *                          @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                          @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList    Additional attributes for this event.
 *  @param threadContingent The thread contingent. References a @eref{Comm}
 *                          definition and will be mapped to the global
 *                          definition if a mapping table of type
 *                          @eref{OTF2_MAPPING_COMM} is available.
 *  @param sequenceCount    A @p threadContingent unique number. The
 *                          corresponding @eref{ThreadWait} event does have
 *                          the same number. @eref{OTF2_UNDEFINED_UINT64} in
 *                          case no corresponding @eref{ThreadWait} event
 *                          exists.
 *
 *  @since Version 1.3
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_ThreadEnd )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CommRef threadContingent,
uint64_t sequenceCount );


/** @brief Registers the callback for the ThreadEnd event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param threadEndCallback        Function which should be called for all
 *                                  @eref{ThreadEnd} definitions.
 *
 *  @since Version 1.3
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadEndCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadEnd threadEndCallback );


/** @brief Callback for the CallingContextEnter event record.
 *
 *  The thread entered an instrumented region, represented by the
 *  referenced @eref{CallingContext}. In contrast to the @eref{Enter}
 *  event, it gives the full calling context through the
 *  @eref{CallingContext} tree.
 *  
 *  Events based on the @eref{CallingContext} definition are mutually
 *  exclusive with the @eref{Enter}/@eref{Leave} events in a trace.
 *  
 *  If no callback for this event is set but a callback for @eref{Enter}
 *  events is defined, the reader will automatically generate an
 *  @eref{Enter} callback call for the @eref{Region} referenced by the
 *  @eref{CallingContext} attribute of this event.  Note that this
 *  emulation does @b not re-create the full calling context!  It only
 *  re-creates the event order for instrumented regions.
 *  
 *  @param locationID     The location where this event happened.
 *  @param time           The time when this event happened.
 *  @param userData       User data as set by
 *                        @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                        @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList  Additional attributes for this event.
 *  @param callingContext The entered region as referenced by the
 *                        @eref{CallingContext} definition. References a
 *                        @eref{CallingContext} definition and will be mapped
 *                        to the global definition if a mapping table of type
 *                        @eref{OTF2_MAPPING_CALLING_CONTEXT} is available.
 *  @param unwindDistance The unwindDistance for this @p callingContext. See the
 *                        description in @eref{CallingContext}.
 *
 *  @since Version 2.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_CallingContextEnter )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance );


/** @brief Registers the callback for the CallingContextEnter event.
 *  
 *  @param globalEvtReaderCallbacks    Struct for all callbacks.
 *  @param callingContextEnterCallback Function which should be called for all
 *                                     @eref{CallingContextEnter}
 *                                     definitions.
 *
 *  @since Version 2.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetCallingContextEnterCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_CallingContextEnter callingContextEnterCallback );


/** @brief Callback for the CallingContextLeave event record.
 *
 *  The thread left an instrumented region, represented by the referenced
 *  @eref{CallingContext}. In contrast to the @eref{Leave} event, it
 *  gives the full calling context through the @eref{CallingContext}
 *  tree.
 *  
 *  The unwind distance for this @eref{CallingContext} is defined to be 1.
 *  Because it must be assumed that the instrumented region made
 *  progress since the previous @eref{CallingContext} event.
 *  
 *  Events based on the @eref{CallingContext} definition are mutually
 *  exclusive with the @eref{Enter}/@eref{Leave} events in a trace.
 *  
 *  The parent of the @eref{CallingContext} must be used as the previous
 *  calling context for the next event.
 *  
 *  If no callback for this event is set but a callback for @eref{Leave}
 *  events is defined, the reader will automatically generate an
 *  @eref{Leave} callback call for the @eref{Region} referenced by the
 *  @eref{CallingContext} attribute of this event.  Note that this
 *  emulation does @b not re-create the full calling context!  It only
 *  re-creates the event order for instrumented regions.
 *  
 *  @param locationID     The location where this event happened.
 *  @param time           The time when this event happened.
 *  @param userData       User data as set by
 *                        @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                        @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList  Additional attributes for this event.
 *  @param callingContext The left region as referenced by the
 *                        @eref{CallingContext} definition. References a
 *                        @eref{CallingContext} definition and will be mapped
 *                        to the global definition if a mapping table of type
 *                        @eref{OTF2_MAPPING_CALLING_CONTEXT} is available.
 *
 *  @since Version 2.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_CallingContextLeave )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext );


/** @brief Registers the callback for the CallingContextLeave event.
 *  
 *  @param globalEvtReaderCallbacks    Struct for all callbacks.
 *  @param callingContextLeaveCallback Function which should be called for all
 *                                     @eref{CallingContextLeave}
 *                                     definitions.
 *
 *  @since Version 2.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetCallingContextLeaveCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_CallingContextLeave callingContextLeaveCallback );


/** @brief Callback for the CallingContextSample event record.
 *
 *  The thread was interrupted to take a sample of its current state
 *  (region and source code location).
 *  
 *  Events based on the @eref{CallingContext} definition are mutually
 *  exclusive with the @eref{Enter}/@eref{Leave} events in a trace.
 *  
 *  @param locationID         The location where this event happened.
 *  @param time               The time when this event happened.
 *  @param userData           User data as set by
 *                            @eref{OTF2_Reader_RegisterGlobalEvtCallbacks}
 *                            or @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList      Additional attributes for this event.
 *  @param callingContext     Describes the calling context of the thread when it
 *                            was interrupted. References a
 *                            @eref{CallingContext} definition and will be
 *                            mapped to the global definition if a mapping
 *                            table of type
 *                            @eref{OTF2_MAPPING_CALLING_CONTEXT} is
 *                            available.
 *  @param unwindDistance     The unwindDistance for this @p callingContext. See
 *                            the description in @eref{CallingContext}.
 *  @param interruptGenerator  References a @eref{InterruptGenerator} definition
 *                            and will be mapped to the global definition if
 *                            a mapping table of type
 *                            @eref{OTF2_MAPPING_INTERRUPT_GENERATOR} is
 *                            available.
 *
 *  @since Version 1.5
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_CallingContextSample )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_CallingContextRef callingContext,
uint32_t unwindDistance,
OTF2_InterruptGeneratorRef interruptGenerator );


/** @brief Registers the callback for the CallingContextSample event.
 *  
 *  @param globalEvtReaderCallbacks     Struct for all callbacks.
 *  @param callingContextSampleCallback Function which should be called for all
 *                                      @eref{CallingContextSample}
 *                                      definitions.
 *
 *  @since Version 1.5
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetCallingContextSampleCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_CallingContextSample callingContextSampleCallback );


/** @brief Callback for the TaskCreate event record.
 *
 *  TaskCreate indicates that a lightweight task was created.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_TaskCreate )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


/** @brief Registers the callback for the TaskCreate event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param taskCreateCallback       Function which should be called for all
 *                                  @eref{TaskCreate} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetTaskCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_TaskCreate taskCreateCallback );


/** @brief Callback for the TaskDestroy event record.
 *
 *  TaskDestroy indicates that a lightweight task was destroyed.
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_TaskDestroy )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


/** @brief Registers the callback for the TaskDestroy event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param taskDestroyCallback      Function which should be called for all
 *                                  @eref{TaskDestroy} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetTaskDestroyCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_TaskDestroy taskDestroyCallback );


/** @brief Callback for the TaskRunnable event record.
 *
 *  TaskRunnable
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_TaskRunnable )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


/** @brief Registers the callback for the TaskRunnable event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param taskRunnableCallback     Function which should be called for all
 *                                  @eref{TaskRunnable} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetTaskRunnableCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_TaskRunnable taskRunnableCallback );


/** @brief Callback for the AddDependence event record.
 *
 *  AddDependence
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param src           Source of dependence References a @eref{Region}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *  @param dest          Destination of dependence References a @eref{Region}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_AddDependence )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef src,
OTF2_RegionRef dest );


/** @brief Registers the callback for the AddDependence event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param addDependenceCallback    Function which should be called for all
 *                                  @eref{AddDependence} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetAddDependenceCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_AddDependence addDependenceCallback );


/** @brief Callback for the SatisfyDependence event record.
 *
 *  SatisfyDependence
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param src           Source of dependence References a @eref{Region}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *  @param dest          Destination of dependence References a @eref{Region}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_SatisfyDependence )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef src,
OTF2_RegionRef dest );


/** @brief Registers the callback for the SatisfyDependence event.
 *  
 *  @param globalEvtReaderCallbacks  Struct for all callbacks.
 *  @param satisfyDependenceCallback Function which should be called for all
 *                                   @eref{SatisfyDependence} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetSatisfyDependenceCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_SatisfyDependence satisfyDependenceCallback );


/** @brief Callback for the DataAcquire event record.
 *
 *  DataAcquire
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param task          Task acquiring datablock References a @eref{Region}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *  @param data          Datablock being acquired References a @eref{Region}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *  @param size          Size of datablock being acquired
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_DataAcquire )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef task,
OTF2_RegionRef data,
uint64_t size );


/** @brief Registers the callback for the DataAcquire event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param dataAcquireCallback      Function which should be called for all
 *                                  @eref{DataAcquire} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetDataAcquireCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_DataAcquire dataAcquireCallback );


/** @brief Callback for the DataRelease event record.
 *
 *  DataRelease
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param task          Task releasing datablock References a @eref{Region}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *  @param data          Datablock being released References a @eref{Region}
 *                       definition and will be mapped to the global
 *                       definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *  @param size          Size of datablock being released
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_DataRelease )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef task,
OTF2_RegionRef data,
uint64_t size );


/** @brief Registers the callback for the DataRelease event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param dataReleaseCallback      Function which should be called for all
 *                                  @eref{DataRelease} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetDataReleaseCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_DataRelease dataReleaseCallback );


/** @brief Callback for the EventCreate event record.
 *
 *  EventCreate
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_EventCreate )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


/** @brief Registers the callback for the EventCreate event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param eventCreateCallback      Function which should be called for all
 *                                  @eref{EventCreate} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetEventCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_EventCreate eventCreateCallback );


/** @brief Callback for the EventDestroy event record.
 *
 *  EventDestroy
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_EventDestroy )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


/** @brief Registers the callback for the EventDestroy event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param eventDestroyCallback     Function which should be called for all
 *                                  @eref{EventDestroy} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetEventDestroyCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_EventDestroy eventDestroyCallback );


/** @brief Callback for the DataCreate event record.
 *
 *  DataCreate
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *  @param size          Size of datablock
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_DataCreate )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region,
uint64_t size );


/** @brief Registers the callback for the DataCreate event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param dataCreateCallback       Function which should be called for all
 *                                  @eref{DataCreate} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetDataCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_DataCreate dataCreateCallback );


/** @brief Callback for the DataDestroy event record.
 *
 *  DataDestroy
 *  
 *  @param locationID    The location where this event happened.
 *  @param time          The time when this event happened.
 *  @param userData      User data as set by
 *                       @eref{OTF2_Reader_RegisterGlobalEvtCallbacks} or
 *                       @eref{OTF2_GlobalEvtReader_SetCallbacks}.
 *  @param attributeList Additional attributes for this event.
 *  @param region        Needs to be defined in a definition record References a
 *                       @eref{Region} definition and will be mapped to the
 *                       global definition if a mapping table of type
 *                       @eref{OTF2_MAPPING_REGION} is available.
 *
 *  @since Version 1.0
 *
 *  @return @eref{OTF2_CALLBACK_SUCCESS} or @eref{OTF2_CALLBACK_INTERRUPT}.
 */
typedef OTF2_CallbackCode
( *OTF2_GlobalEvtReaderCallback_DataDestroy )( OTF2_LocationRef    locationID,
                                                  OTF2_TimeStamp      time,
                                                  void*               userData,
                                                  OTF2_AttributeList* attributeList,
OTF2_RegionRef region );


/** @brief Registers the callback for the DataDestroy event.
 *  
 *  @param globalEvtReaderCallbacks Struct for all callbacks.
 *  @param dataDestroyCallback      Function which should be called for all
 *                                  @eref{DataDestroy} definitions.
 *
 *  @since Version 1.0
 *
 *  @retbegin
 *    @retcode{OTF2_SUCCESS, if successful}
 *    @retcode{OTF2_ERROR_INVALID_ARGUMENT,
 *             for an invalid @p defReaderCallbacks argument}
 *  @retend
 */
OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetDataDestroyCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_DataDestroy dataDestroyCallback );


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* !OTF2_GLOBAL_EVT_READER_CALLBACKS_H */
