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


/**
 *  @file
 *  @source     templates/OTF2_GlobalEvtReader_inc.tmpl.c
 *
 *  @brief      This module reads the global events. This means that the
 *              programmer must first select a set of locations a register
 *              callbacks, and then gets a merged stream of records from
 *              these selected locations. Rudimentary filtering could be
 *              done by registering only callbacks for the needed record
 *              types. This is an external interface.
 */




static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_buffer_flush( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_BufferFlush* record = &event->record.buffer_flush;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.buffer_flush )
    {
        interrupt = reader->reader_callbacks.buffer_flush( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->stop_time );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_measurement_on_off( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MeasurementOnOff* record = &event->record.measurement_on_off;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.measurement_on_off )
    {
        interrupt = reader->reader_callbacks.measurement_on_off( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->measurement_mode );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_enter( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_Enter* record = &event->record.enter;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.enter )
    {
        interrupt = reader->reader_callbacks.enter( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_leave( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_Leave* record = &event->record.leave;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.leave )
    {
        interrupt = reader->reader_callbacks.leave( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_send( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiSend* record = &event->record.mpi_send;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_send )
    {
        interrupt = reader->reader_callbacks.mpi_send( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->receiver,
record->communicator,
record->msg_tag,
record->msg_length );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_isend( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiIsend* record = &event->record.mpi_isend;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_isend )
    {
        interrupt = reader->reader_callbacks.mpi_isend( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->receiver,
record->communicator,
record->msg_tag,
record->msg_length,
record->request_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_isend_complete( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiIsendComplete* record = &event->record.mpi_isend_complete;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_isend_complete )
    {
        interrupt = reader->reader_callbacks.mpi_isend_complete( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->request_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_irecv_request( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiIrecvRequest* record = &event->record.mpi_irecv_request;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_irecv_request )
    {
        interrupt = reader->reader_callbacks.mpi_irecv_request( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->request_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_recv( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiRecv* record = &event->record.mpi_recv;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_recv )
    {
        interrupt = reader->reader_callbacks.mpi_recv( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->sender,
record->communicator,
record->msg_tag,
record->msg_length );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_irecv( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiIrecv* record = &event->record.mpi_irecv;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_irecv )
    {
        interrupt = reader->reader_callbacks.mpi_irecv( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->sender,
record->communicator,
record->msg_tag,
record->msg_length,
record->request_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_request_test( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiRequestTest* record = &event->record.mpi_request_test;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_request_test )
    {
        interrupt = reader->reader_callbacks.mpi_request_test( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->request_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_request_cancelled( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiRequestCancelled* record = &event->record.mpi_request_cancelled;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_request_cancelled )
    {
        interrupt = reader->reader_callbacks.mpi_request_cancelled( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->request_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_collective_begin( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiCollectiveBegin* record = &event->record.mpi_collective_begin;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_collective_begin )
    {
        interrupt = reader->reader_callbacks.mpi_collective_begin( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_mpi_collective_end( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_MpiCollectiveEnd* record = &event->record.mpi_collective_end;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.mpi_collective_end )
    {
        interrupt = reader->reader_callbacks.mpi_collective_end( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->collective_op,
record->communicator,
record->root,
record->size_sent,
record->size_received );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_omp_fork( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_OmpFork* record = &event->record.omp_fork;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.omp_fork )
    {
        interrupt = reader->reader_callbacks.omp_fork( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->number_of_requested_threads );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_omp_join( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_OmpJoin* record = &event->record.omp_join;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.omp_join )
    {
        interrupt = reader->reader_callbacks.omp_join( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_omp_acquire_lock( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_OmpAcquireLock* record = &event->record.omp_acquire_lock;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.omp_acquire_lock )
    {
        interrupt = reader->reader_callbacks.omp_acquire_lock( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->lock_id,
record->acquisition_order );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_omp_release_lock( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_OmpReleaseLock* record = &event->record.omp_release_lock;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.omp_release_lock )
    {
        interrupt = reader->reader_callbacks.omp_release_lock( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->lock_id,
record->acquisition_order );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_omp_task_create( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_OmpTaskCreate* record = &event->record.omp_task_create;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.omp_task_create )
    {
        interrupt = reader->reader_callbacks.omp_task_create( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->task_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_omp_task_switch( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_OmpTaskSwitch* record = &event->record.omp_task_switch;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.omp_task_switch )
    {
        interrupt = reader->reader_callbacks.omp_task_switch( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->task_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_omp_task_complete( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_OmpTaskComplete* record = &event->record.omp_task_complete;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.omp_task_complete )
    {
        interrupt = reader->reader_callbacks.omp_task_complete( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->task_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_metric( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_Metric* record = &event->record.metric;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.metric )
    {
        interrupt = reader->reader_callbacks.metric( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->metric,
record->number_of_metrics,
record->type_ids,
record->metric_values );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );

    free( record->type_ids );
    free( record->metric_values );

    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_parameter_string( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ParameterString* record = &event->record.parameter_string;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.parameter_string )
    {
        interrupt = reader->reader_callbacks.parameter_string( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->parameter,
record->string );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_parameter_int( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ParameterInt* record = &event->record.parameter_int;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.parameter_int )
    {
        interrupt = reader->reader_callbacks.parameter_int( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->parameter,
record->value );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_parameter_unsigned_int( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ParameterUnsignedInt* record = &event->record.parameter_unsigned_int;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.parameter_unsigned_int )
    {
        interrupt = reader->reader_callbacks.parameter_unsigned_int( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->parameter,
record->value );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_win_create( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaWinCreate* record = &event->record.rma_win_create;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_win_create )
    {
        interrupt = reader->reader_callbacks.rma_win_create( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_win_destroy( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaWinDestroy* record = &event->record.rma_win_destroy;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_win_destroy )
    {
        interrupt = reader->reader_callbacks.rma_win_destroy( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_collective_begin( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaCollectiveBegin* record = &event->record.rma_collective_begin;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_collective_begin )
    {
        interrupt = reader->reader_callbacks.rma_collective_begin( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_collective_end( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaCollectiveEnd* record = &event->record.rma_collective_end;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_collective_end )
    {
        interrupt = reader->reader_callbacks.rma_collective_end( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->collective_op,
record->sync_level,
record->win,
record->root,
record->bytes_sent,
record->bytes_received );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_group_sync( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaGroupSync* record = &event->record.rma_group_sync;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_group_sync )
    {
        interrupt = reader->reader_callbacks.rma_group_sync( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->sync_level,
record->win,
record->group );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_request_lock( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaRequestLock* record = &event->record.rma_request_lock;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_request_lock )
    {
        interrupt = reader->reader_callbacks.rma_request_lock( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->remote,
record->lock_id,
record->lock_type );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_acquire_lock( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaAcquireLock* record = &event->record.rma_acquire_lock;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_acquire_lock )
    {
        interrupt = reader->reader_callbacks.rma_acquire_lock( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->remote,
record->lock_id,
record->lock_type );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_try_lock( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaTryLock* record = &event->record.rma_try_lock;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_try_lock )
    {
        interrupt = reader->reader_callbacks.rma_try_lock( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->remote,
record->lock_id,
record->lock_type );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_release_lock( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaReleaseLock* record = &event->record.rma_release_lock;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_release_lock )
    {
        interrupt = reader->reader_callbacks.rma_release_lock( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->remote,
record->lock_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_sync( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaSync* record = &event->record.rma_sync;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_sync )
    {
        interrupt = reader->reader_callbacks.rma_sync( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->remote,
record->sync_type );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_wait_change( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaWaitChange* record = &event->record.rma_wait_change;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_wait_change )
    {
        interrupt = reader->reader_callbacks.rma_wait_change( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_put( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaPut* record = &event->record.rma_put;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_put )
    {
        interrupt = reader->reader_callbacks.rma_put( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->remote,
record->bytes,
record->matching_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_get( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaGet* record = &event->record.rma_get;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_get )
    {
        interrupt = reader->reader_callbacks.rma_get( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->remote,
record->bytes,
record->matching_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_atomic( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaAtomic* record = &event->record.rma_atomic;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_atomic )
    {
        interrupt = reader->reader_callbacks.rma_atomic( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->remote,
record->type,
record->bytes_sent,
record->bytes_received,
record->matching_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_op_complete_blocking( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaOpCompleteBlocking* record = &event->record.rma_op_complete_blocking;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_op_complete_blocking )
    {
        interrupt = reader->reader_callbacks.rma_op_complete_blocking( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->matching_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_op_complete_non_blocking( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaOpCompleteNonBlocking* record = &event->record.rma_op_complete_non_blocking;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_op_complete_non_blocking )
    {
        interrupt = reader->reader_callbacks.rma_op_complete_non_blocking( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->matching_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_op_test( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaOpTest* record = &event->record.rma_op_test;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_op_test )
    {
        interrupt = reader->reader_callbacks.rma_op_test( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->matching_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_rma_op_complete_remote( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_RmaOpCompleteRemote* record = &event->record.rma_op_complete_remote;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.rma_op_complete_remote )
    {
        interrupt = reader->reader_callbacks.rma_op_complete_remote( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->win,
record->matching_id );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_fork( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadFork* record = &event->record.thread_fork;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_fork )
    {
        interrupt = reader->reader_callbacks.thread_fork( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->model,
record->number_of_requested_threads );
    }
    else if ( reader->reader_callbacks.omp_fork )
    {
        OTF2_OmpFork omp_fork_record;
        bool conversion_successful
            = otf2_event_thread_fork_convert_to_omp_fork( reader->archive,
                                                                                       record,
                                                                                       &evt_reader->attribute_list,
                                                                                       &omp_fork_record );
        if ( conversion_successful )
        {
            interrupt = reader->reader_callbacks.omp_fork( evt_reader->location_id,
                                                                                    record->time,
                                                                                    reader->user_data,
                                                                                    &evt_reader->attribute_list,
omp_fork_record.number_of_requested_threads );
        }
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_join( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadJoin* record = &event->record.thread_join;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_join )
    {
        interrupt = reader->reader_callbacks.thread_join( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->model );
    }
    else if ( reader->reader_callbacks.omp_join )
    {
        OTF2_OmpJoin omp_join_record;
        bool conversion_successful
            = otf2_event_thread_join_convert_to_omp_join( reader->archive,
                                                                                       record,
                                                                                       &evt_reader->attribute_list,
                                                                                       &omp_join_record );
        if ( conversion_successful )
        {
            interrupt = reader->reader_callbacks.omp_join( evt_reader->location_id,
                                                                                    record->time,
                                                                                    reader->user_data,
                                                                                    &evt_reader->attribute_list );
        }
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_team_begin( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadTeamBegin* record = &event->record.thread_team_begin;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_team_begin )
    {
        interrupt = reader->reader_callbacks.thread_team_begin( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_team );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_team_end( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadTeamEnd* record = &event->record.thread_team_end;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_team_end )
    {
        interrupt = reader->reader_callbacks.thread_team_end( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_team );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_acquire_lock( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadAcquireLock* record = &event->record.thread_acquire_lock;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_acquire_lock )
    {
        interrupt = reader->reader_callbacks.thread_acquire_lock( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->model,
record->lock_id,
record->acquisition_order );
    }
    else if ( reader->reader_callbacks.omp_acquire_lock )
    {
        OTF2_OmpAcquireLock omp_acquire_lock_record;
        bool conversion_successful
            = otf2_event_thread_acquire_lock_convert_to_omp_acquire_lock( reader->archive,
                                                                                       record,
                                                                                       &evt_reader->attribute_list,
                                                                                       &omp_acquire_lock_record );
        if ( conversion_successful )
        {
            interrupt = reader->reader_callbacks.omp_acquire_lock( evt_reader->location_id,
                                                                                    record->time,
                                                                                    reader->user_data,
                                                                                    &evt_reader->attribute_list,
omp_acquire_lock_record.lock_id,
omp_acquire_lock_record.acquisition_order );
        }
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_release_lock( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadReleaseLock* record = &event->record.thread_release_lock;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_release_lock )
    {
        interrupt = reader->reader_callbacks.thread_release_lock( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->model,
record->lock_id,
record->acquisition_order );
    }
    else if ( reader->reader_callbacks.omp_release_lock )
    {
        OTF2_OmpReleaseLock omp_release_lock_record;
        bool conversion_successful
            = otf2_event_thread_release_lock_convert_to_omp_release_lock( reader->archive,
                                                                                       record,
                                                                                       &evt_reader->attribute_list,
                                                                                       &omp_release_lock_record );
        if ( conversion_successful )
        {
            interrupt = reader->reader_callbacks.omp_release_lock( evt_reader->location_id,
                                                                                    record->time,
                                                                                    reader->user_data,
                                                                                    &evt_reader->attribute_list,
omp_release_lock_record.lock_id,
omp_release_lock_record.acquisition_order );
        }
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_task_create( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadTaskCreate* record = &event->record.thread_task_create;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_task_create )
    {
        interrupt = reader->reader_callbacks.thread_task_create( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_team,
record->creating_thread,
record->generation_number );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_task_switch( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadTaskSwitch* record = &event->record.thread_task_switch;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_task_switch )
    {
        interrupt = reader->reader_callbacks.thread_task_switch( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_team,
record->creating_thread,
record->generation_number );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_task_complete( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadTaskComplete* record = &event->record.thread_task_complete;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_task_complete )
    {
        interrupt = reader->reader_callbacks.thread_task_complete( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_team,
record->creating_thread,
record->generation_number );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_create( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadCreate* record = &event->record.thread_create;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_create )
    {
        interrupt = reader->reader_callbacks.thread_create( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_contingent,
record->sequence_count );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_begin( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadBegin* record = &event->record.thread_begin;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_begin )
    {
        interrupt = reader->reader_callbacks.thread_begin( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_contingent,
record->sequence_count );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_wait( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadWait* record = &event->record.thread_wait;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_wait )
    {
        interrupt = reader->reader_callbacks.thread_wait( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_contingent,
record->sequence_count );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_thread_end( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_ThreadEnd* record = &event->record.thread_end;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.thread_end )
    {
        interrupt = reader->reader_callbacks.thread_end( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->thread_contingent,
record->sequence_count );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_calling_context_enter( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_CallingContextEnter* record = &event->record.calling_context_enter;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.calling_context_enter )
    {
        interrupt = reader->reader_callbacks.calling_context_enter( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->calling_context,
record->unwind_distance );
    }
    else if ( reader->reader_callbacks.enter )
    {
        OTF2_Enter enter_record;
        bool conversion_successful
            = otf2_event_calling_context_enter_convert_to_enter( reader->archive,
                                                                                       record,
                                                                                       &evt_reader->attribute_list,
                                                                                       &enter_record );
        if ( conversion_successful )
        {
            interrupt = reader->reader_callbacks.enter( evt_reader->location_id,
                                                                                    record->time,
                                                                                    reader->user_data,
                                                                                    &evt_reader->attribute_list,
enter_record.region );
        }
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_calling_context_leave( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_CallingContextLeave* record = &event->record.calling_context_leave;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.calling_context_leave )
    {
        interrupt = reader->reader_callbacks.calling_context_leave( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->calling_context );
    }
    else if ( reader->reader_callbacks.leave )
    {
        OTF2_Leave leave_record;
        bool conversion_successful
            = otf2_event_calling_context_leave_convert_to_leave( reader->archive,
                                                                                       record,
                                                                                       &evt_reader->attribute_list,
                                                                                       &leave_record );
        if ( conversion_successful )
        {
            interrupt = reader->reader_callbacks.leave( evt_reader->location_id,
                                                                                    record->time,
                                                                                    reader->user_data,
                                                                                    &evt_reader->attribute_list,
leave_record.region );
        }
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_calling_context_sample( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_CallingContextSample* record = &event->record.calling_context_sample;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.calling_context_sample )
    {
        interrupt = reader->reader_callbacks.calling_context_sample( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->calling_context,
record->unwind_distance,
record->interrupt_generator );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_task_create( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_TaskCreate* record = &event->record.task_create;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.task_create )
    {
        interrupt = reader->reader_callbacks.task_create( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_task_destroy( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_TaskDestroy* record = &event->record.task_destroy;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.task_destroy )
    {
        interrupt = reader->reader_callbacks.task_destroy( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_task_runnable( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_TaskRunnable* record = &event->record.task_runnable;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.task_runnable )
    {
        interrupt = reader->reader_callbacks.task_runnable( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_add_dependence( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_AddDependence* record = &event->record.add_dependence;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.add_dependence )
    {
        interrupt = reader->reader_callbacks.add_dependence( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->src,
record->dest );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_satisfy_dependence( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_SatisfyDependence* record = &event->record.satisfy_dependence;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.satisfy_dependence )
    {
        interrupt = reader->reader_callbacks.satisfy_dependence( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->src,
record->dest );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_data_acquire( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_DataAcquire* record = &event->record.data_acquire;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.data_acquire )
    {
        interrupt = reader->reader_callbacks.data_acquire( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->task,
record->data,
record->size );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_data_release( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_DataRelease* record = &event->record.data_release;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.data_release )
    {
        interrupt = reader->reader_callbacks.data_release( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->task,
record->data,
record->size );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_event_create( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_EventCreate* record = &event->record.event_create;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.event_create )
    {
        interrupt = reader->reader_callbacks.event_create( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_event_destroy( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_EventDestroy* record = &event->record.event_destroy;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.event_destroy )
    {
        interrupt = reader->reader_callbacks.event_destroy( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_data_create( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_DataCreate* record = &event->record.data_create;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.data_create )
    {
        interrupt = reader->reader_callbacks.data_create( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region,
record->size );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static inline OTF2_ErrorCode
otf2_global_evt_reader_trigger_data_destroy( const OTF2_GlobalEvtReader* reader,
                                                OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event    = &evt_reader->current_event;
    OTF2_DataDestroy* record = &event->record.data_destroy;

    OTF2_CallbackCode interrupt = OTF2_CALLBACK_SUCCESS;
    if ( reader->reader_callbacks.data_destroy )
    {
        interrupt = reader->reader_callbacks.data_destroy( evt_reader->location_id,
                                                              record->time,
                                                              reader->user_data,
                                                              &evt_reader->attribute_list,
record->region );
    }

     /* Before the next event is read, the attribute list has to be cleaned up
      * i.e. remove all attributes from the list. */
    otf2_attribute_list_remove_all_attributes( &evt_reader->attribute_list );


    return OTF2_CALLBACK_SUCCESS == interrupt
           ? OTF2_SUCCESS
           : OTF2_ERROR_INTERRUPTED_BY_CALLBACK;
}


static OTF2_ErrorCode
otf2_global_evt_reader_trigger_callback( const OTF2_GlobalEvtReader* reader,
                                         OTF2_EvtReader*             evt_reader )
{
    OTF2_GenericEvent* event = &evt_reader->current_event;

    switch ( event->type )
    {
        /* An attribute list should not be in the event queue alone. */
        case OTF2_ATTRIBUTE_LIST:
            return OTF2_ERROR_INTEGRITY_FAULT;

        case OTF2_EVENT_BUFFER_FLUSH:
            return otf2_global_evt_reader_trigger_buffer_flush( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MEASUREMENT_ON_OFF:
            return otf2_global_evt_reader_trigger_measurement_on_off( reader,
                                                                   evt_reader );

        case OTF2_EVENT_ENTER:
            return otf2_global_evt_reader_trigger_enter( reader,
                                                                   evt_reader );

        case OTF2_EVENT_LEAVE:
            return otf2_global_evt_reader_trigger_leave( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_SEND:
            return otf2_global_evt_reader_trigger_mpi_send( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_ISEND:
            return otf2_global_evt_reader_trigger_mpi_isend( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_ISEND_COMPLETE:
            return otf2_global_evt_reader_trigger_mpi_isend_complete( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_IRECV_REQUEST:
            return otf2_global_evt_reader_trigger_mpi_irecv_request( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_RECV:
            return otf2_global_evt_reader_trigger_mpi_recv( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_IRECV:
            return otf2_global_evt_reader_trigger_mpi_irecv( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_REQUEST_TEST:
            return otf2_global_evt_reader_trigger_mpi_request_test( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_REQUEST_CANCELLED:
            return otf2_global_evt_reader_trigger_mpi_request_cancelled( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_COLLECTIVE_BEGIN:
            return otf2_global_evt_reader_trigger_mpi_collective_begin( reader,
                                                                   evt_reader );

        case OTF2_EVENT_MPI_COLLECTIVE_END:
            return otf2_global_evt_reader_trigger_mpi_collective_end( reader,
                                                                   evt_reader );

        case OTF2_EVENT_OMP_FORK:
            return otf2_global_evt_reader_trigger_omp_fork( reader,
                                                                   evt_reader );

        case OTF2_EVENT_OMP_JOIN:
            return otf2_global_evt_reader_trigger_omp_join( reader,
                                                                   evt_reader );

        case OTF2_EVENT_OMP_ACQUIRE_LOCK:
            return otf2_global_evt_reader_trigger_omp_acquire_lock( reader,
                                                                   evt_reader );

        case OTF2_EVENT_OMP_RELEASE_LOCK:
            return otf2_global_evt_reader_trigger_omp_release_lock( reader,
                                                                   evt_reader );

        case OTF2_EVENT_OMP_TASK_CREATE:
            return otf2_global_evt_reader_trigger_omp_task_create( reader,
                                                                   evt_reader );

        case OTF2_EVENT_OMP_TASK_SWITCH:
            return otf2_global_evt_reader_trigger_omp_task_switch( reader,
                                                                   evt_reader );

        case OTF2_EVENT_OMP_TASK_COMPLETE:
            return otf2_global_evt_reader_trigger_omp_task_complete( reader,
                                                                   evt_reader );

        case OTF2_EVENT_METRIC:
            return otf2_global_evt_reader_trigger_metric( reader,
                                                                   evt_reader );

        case OTF2_EVENT_PARAMETER_STRING:
            return otf2_global_evt_reader_trigger_parameter_string( reader,
                                                                   evt_reader );

        case OTF2_EVENT_PARAMETER_INT:
            return otf2_global_evt_reader_trigger_parameter_int( reader,
                                                                   evt_reader );

        case OTF2_EVENT_PARAMETER_UNSIGNED_INT:
            return otf2_global_evt_reader_trigger_parameter_unsigned_int( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_WIN_CREATE:
            return otf2_global_evt_reader_trigger_rma_win_create( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_WIN_DESTROY:
            return otf2_global_evt_reader_trigger_rma_win_destroy( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_COLLECTIVE_BEGIN:
            return otf2_global_evt_reader_trigger_rma_collective_begin( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_COLLECTIVE_END:
            return otf2_global_evt_reader_trigger_rma_collective_end( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_GROUP_SYNC:
            return otf2_global_evt_reader_trigger_rma_group_sync( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_REQUEST_LOCK:
            return otf2_global_evt_reader_trigger_rma_request_lock( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_ACQUIRE_LOCK:
            return otf2_global_evt_reader_trigger_rma_acquire_lock( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_TRY_LOCK:
            return otf2_global_evt_reader_trigger_rma_try_lock( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_RELEASE_LOCK:
            return otf2_global_evt_reader_trigger_rma_release_lock( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_SYNC:
            return otf2_global_evt_reader_trigger_rma_sync( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_WAIT_CHANGE:
            return otf2_global_evt_reader_trigger_rma_wait_change( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_PUT:
            return otf2_global_evt_reader_trigger_rma_put( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_GET:
            return otf2_global_evt_reader_trigger_rma_get( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_ATOMIC:
            return otf2_global_evt_reader_trigger_rma_atomic( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_OP_COMPLETE_BLOCKING:
            return otf2_global_evt_reader_trigger_rma_op_complete_blocking( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_OP_COMPLETE_NON_BLOCKING:
            return otf2_global_evt_reader_trigger_rma_op_complete_non_blocking( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_OP_TEST:
            return otf2_global_evt_reader_trigger_rma_op_test( reader,
                                                                   evt_reader );

        case OTF2_EVENT_RMA_OP_COMPLETE_REMOTE:
            return otf2_global_evt_reader_trigger_rma_op_complete_remote( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_FORK:
            return otf2_global_evt_reader_trigger_thread_fork( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_JOIN:
            return otf2_global_evt_reader_trigger_thread_join( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_TEAM_BEGIN:
            return otf2_global_evt_reader_trigger_thread_team_begin( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_TEAM_END:
            return otf2_global_evt_reader_trigger_thread_team_end( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_ACQUIRE_LOCK:
            return otf2_global_evt_reader_trigger_thread_acquire_lock( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_RELEASE_LOCK:
            return otf2_global_evt_reader_trigger_thread_release_lock( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_TASK_CREATE:
            return otf2_global_evt_reader_trigger_thread_task_create( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_TASK_SWITCH:
            return otf2_global_evt_reader_trigger_thread_task_switch( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_TASK_COMPLETE:
            return otf2_global_evt_reader_trigger_thread_task_complete( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_CREATE:
            return otf2_global_evt_reader_trigger_thread_create( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_BEGIN:
            return otf2_global_evt_reader_trigger_thread_begin( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_WAIT:
            return otf2_global_evt_reader_trigger_thread_wait( reader,
                                                                   evt_reader );

        case OTF2_EVENT_THREAD_END:
            return otf2_global_evt_reader_trigger_thread_end( reader,
                                                                   evt_reader );

        case OTF2_EVENT_CALLING_CONTEXT_ENTER:
            return otf2_global_evt_reader_trigger_calling_context_enter( reader,
                                                                   evt_reader );

        case OTF2_EVENT_CALLING_CONTEXT_LEAVE:
            return otf2_global_evt_reader_trigger_calling_context_leave( reader,
                                                                   evt_reader );

        case OTF2_EVENT_CALLING_CONTEXT_SAMPLE:
            return otf2_global_evt_reader_trigger_calling_context_sample( reader,
                                                                   evt_reader );

        case OTF2_EVENT_TASK_CREATE:
            return otf2_global_evt_reader_trigger_task_create( reader,
                                                                   evt_reader );

        case OTF2_EVENT_TASK_DESTROY:
            return otf2_global_evt_reader_trigger_task_destroy( reader,
                                                                   evt_reader );

        case OTF2_EVENT_TASK_RUNNABLE:
            return otf2_global_evt_reader_trigger_task_runnable( reader,
                                                                   evt_reader );

        case OTF2_EVENT_ADD_DEPENDENCE:
            return otf2_global_evt_reader_trigger_add_dependence( reader,
                                                                   evt_reader );

        case OTF2_EVENT_SATISFY_DEPENDENCE:
            return otf2_global_evt_reader_trigger_satisfy_dependence( reader,
                                                                   evt_reader );

        case OTF2_EVENT_DATA_ACQUIRE:
            return otf2_global_evt_reader_trigger_data_acquire( reader,
                                                                   evt_reader );

        case OTF2_EVENT_DATA_RELEASE:
            return otf2_global_evt_reader_trigger_data_release( reader,
                                                                   evt_reader );

        case OTF2_EVENT_EVENT_CREATE:
            return otf2_global_evt_reader_trigger_event_create( reader,
                                                                   evt_reader );

        case OTF2_EVENT_EVENT_DESTROY:
            return otf2_global_evt_reader_trigger_event_destroy( reader,
                                                                   evt_reader );

        case OTF2_EVENT_DATA_CREATE:
            return otf2_global_evt_reader_trigger_data_create( reader,
                                                                   evt_reader );

        case OTF2_EVENT_DATA_DESTROY:
            return otf2_global_evt_reader_trigger_data_destroy( reader,
                                                                   evt_reader );

        default:
            return otf2_global_evt_reader_trigger_unknown( reader,
                                                           evt_reader );
    }
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetBufferFlushCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_BufferFlush bufferFlushCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->buffer_flush = bufferFlushCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMeasurementOnOffCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MeasurementOnOff measurementOnOffCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->measurement_on_off = measurementOnOffCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetEnterCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_Enter enterCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->enter = enterCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetLeaveCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_Leave leaveCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->leave = leaveCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiSendCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiSend mpiSendCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_send = mpiSendCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiIsendCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiIsend mpiIsendCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_isend = mpiIsendCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiIsendCompleteCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiIsendComplete mpiIsendCompleteCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_isend_complete = mpiIsendCompleteCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiIrecvRequestCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiIrecvRequest mpiIrecvRequestCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_irecv_request = mpiIrecvRequestCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiRecvCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiRecv mpiRecvCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_recv = mpiRecvCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiIrecvCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiIrecv mpiIrecvCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_irecv = mpiIrecvCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiRequestTestCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiRequestTest mpiRequestTestCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_request_test = mpiRequestTestCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiRequestCancelledCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiRequestCancelled mpiRequestCancelledCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_request_cancelled = mpiRequestCancelledCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiCollectiveBeginCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiCollectiveBegin mpiCollectiveBeginCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_collective_begin = mpiCollectiveBeginCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMpiCollectiveEndCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_MpiCollectiveEnd mpiCollectiveEndCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->mpi_collective_end = mpiCollectiveEndCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpForkCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpFork ompForkCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->omp_fork = ompForkCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpJoinCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpJoin ompJoinCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->omp_join = ompJoinCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpAcquireLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpAcquireLock ompAcquireLockCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->omp_acquire_lock = ompAcquireLockCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpReleaseLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpReleaseLock ompReleaseLockCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->omp_release_lock = ompReleaseLockCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpTaskCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpTaskCreate ompTaskCreateCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->omp_task_create = ompTaskCreateCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpTaskSwitchCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpTaskSwitch ompTaskSwitchCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->omp_task_switch = ompTaskSwitchCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetOmpTaskCompleteCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_OmpTaskComplete ompTaskCompleteCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->omp_task_complete = ompTaskCompleteCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetMetricCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_Metric metricCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->metric = metricCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetParameterStringCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ParameterString parameterStringCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->parameter_string = parameterStringCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetParameterIntCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ParameterInt parameterIntCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->parameter_int = parameterIntCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetParameterUnsignedIntCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ParameterUnsignedInt parameterUnsignedIntCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->parameter_unsigned_int = parameterUnsignedIntCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaWinCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaWinCreate rmaWinCreateCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_win_create = rmaWinCreateCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaWinDestroyCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaWinDestroy rmaWinDestroyCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_win_destroy = rmaWinDestroyCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaCollectiveBeginCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaCollectiveBegin rmaCollectiveBeginCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_collective_begin = rmaCollectiveBeginCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaCollectiveEndCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaCollectiveEnd rmaCollectiveEndCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_collective_end = rmaCollectiveEndCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaGroupSyncCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaGroupSync rmaGroupSyncCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_group_sync = rmaGroupSyncCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaRequestLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaRequestLock rmaRequestLockCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_request_lock = rmaRequestLockCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaAcquireLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaAcquireLock rmaAcquireLockCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_acquire_lock = rmaAcquireLockCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaTryLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaTryLock rmaTryLockCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_try_lock = rmaTryLockCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaReleaseLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaReleaseLock rmaReleaseLockCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_release_lock = rmaReleaseLockCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaSyncCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaSync rmaSyncCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_sync = rmaSyncCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaWaitChangeCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaWaitChange rmaWaitChangeCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_wait_change = rmaWaitChangeCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaPutCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaPut rmaPutCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_put = rmaPutCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaGetCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaGet rmaGetCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_get = rmaGetCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaAtomicCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaAtomic rmaAtomicCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_atomic = rmaAtomicCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteBlockingCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaOpCompleteBlocking rmaOpCompleteBlockingCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_op_complete_blocking = rmaOpCompleteBlockingCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteNonBlockingCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaOpCompleteNonBlocking rmaOpCompleteNonBlockingCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_op_complete_non_blocking = rmaOpCompleteNonBlockingCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaOpTestCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaOpTest rmaOpTestCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_op_test = rmaOpTestCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetRmaOpCompleteRemoteCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_RmaOpCompleteRemote rmaOpCompleteRemoteCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->rma_op_complete_remote = rmaOpCompleteRemoteCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadForkCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadFork threadForkCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_fork = threadForkCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadJoinCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadJoin threadJoinCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_join = threadJoinCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTeamBeginCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTeamBegin threadTeamBeginCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_team_begin = threadTeamBeginCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTeamEndCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTeamEnd threadTeamEndCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_team_end = threadTeamEndCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadAcquireLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadAcquireLock threadAcquireLockCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_acquire_lock = threadAcquireLockCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadReleaseLockCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadReleaseLock threadReleaseLockCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_release_lock = threadReleaseLockCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTaskCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTaskCreate threadTaskCreateCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_task_create = threadTaskCreateCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTaskSwitchCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTaskSwitch threadTaskSwitchCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_task_switch = threadTaskSwitchCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadTaskCompleteCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadTaskComplete threadTaskCompleteCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_task_complete = threadTaskCompleteCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadCreate threadCreateCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_create = threadCreateCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadBeginCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadBegin threadBeginCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_begin = threadBeginCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadWaitCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadWait threadWaitCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_wait = threadWaitCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetThreadEndCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_ThreadEnd threadEndCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->thread_end = threadEndCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetCallingContextEnterCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_CallingContextEnter callingContextEnterCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->calling_context_enter = callingContextEnterCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetCallingContextLeaveCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_CallingContextLeave callingContextLeaveCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->calling_context_leave = callingContextLeaveCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetCallingContextSampleCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_CallingContextSample callingContextSampleCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->calling_context_sample = callingContextSampleCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetTaskCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_TaskCreate taskCreateCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->task_create = taskCreateCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetTaskDestroyCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_TaskDestroy taskDestroyCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->task_destroy = taskDestroyCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetTaskRunnableCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_TaskRunnable taskRunnableCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->task_runnable = taskRunnableCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetAddDependenceCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_AddDependence addDependenceCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->add_dependence = addDependenceCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetSatisfyDependenceCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_SatisfyDependence satisfyDependenceCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->satisfy_dependence = satisfyDependenceCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetDataAcquireCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_DataAcquire dataAcquireCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->data_acquire = dataAcquireCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetDataReleaseCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_DataRelease dataReleaseCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->data_release = dataReleaseCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetEventCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_EventCreate eventCreateCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->event_create = eventCreateCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetEventDestroyCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_EventDestroy eventDestroyCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->event_destroy = eventDestroyCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetDataCreateCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_DataCreate dataCreateCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->data_create = dataCreateCallback;

    return OTF2_SUCCESS;
}


OTF2_ErrorCode
OTF2_GlobalEvtReaderCallbacks_SetDataDestroyCallback(
    OTF2_GlobalEvtReaderCallbacks*              globalEvtReaderCallbacks,
    OTF2_GlobalEvtReaderCallback_DataDestroy dataDestroyCallback )
{
    if ( !globalEvtReaderCallbacks )
    {
        return UTILS_ERROR( OTF2_ERROR_INVALID_ARGUMENT,
                             "Invalid globalEvtReaderCallback argument!" );
    }

    globalEvtReaderCallbacks->data_destroy = dataDestroyCallback;

    return OTF2_SUCCESS;
}

