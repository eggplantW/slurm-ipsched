/*****************************************************************************\
 *  acct_policy.h - definitions of functions in acct_policy.c
 *****************************************************************************
 *  Copyright (C) 2008 Lawrence Livermore National Security.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Morris Jette <jette@llnl.gov> et. al.
 *  CODE-OCEC-09-009. All rights reserved.
 *
 *  This file is part of SLURM, a resource management program.
 *  For details, see <http://www.schedmd.com/slurmdocs/>.
 *  Please also read the included file: DISCLAIMER.
 *
 *  SLURM is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  In addition, as a special exception, the copyright holders give permission
 *  to link the code of portions of this program with the OpenSSL library under
 *  certain conditions as described in each individual source file, and
 *  distribute linked combinations including the two. You must obey the GNU
 *  General Public License in all respects for all of the code used other than
 *  OpenSSL. If you modify file(s) with this exception, you may extend this
 *  exception to your version of the file(s), but you are not obligated to do
 *  so. If you do not wish to do so, delete this exception statement from your
 *  version.  If you delete this exception statement from all source files in
 *  the program, then also delete it here.
 *
 *  SLURM is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with SLURM; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
\*****************************************************************************/

#ifndef _HAVE_ACCT_POLICY_H
#define _HAVE_ACCT_POLICY_H

#define ADMIN_SET_LIMIT 0xffff

/*
 * acct_policy_add_job_submit - Note that a job has been submitted for
 *	accounting policy purposes.
 */
extern void acct_policy_add_job_submit(struct job_record *job_ptr);

/*
 * acct_policy_remove_job_submit - Note that a job has finished (might
 *      not had started or been allocated resources) for accounting
 *      policy purposes.
 */
extern void acct_policy_remove_job_submit(struct job_record *job_ptr);

/*
 * acct_policy_job_begin - Note that a job is starting for accounting
 *	policy purposes.
 */
extern void acct_policy_job_begin(struct job_record *job_ptr);

/*
 * acct_policy_job_fini - Note that a job is completing for accounting
 *	policy purposes.
 */
extern void acct_policy_job_fini(struct job_record *job_ptr);

extern bool acct_policy_validate(job_desc_msg_t *job_desc,
				 struct part_record *part_ptr,
				 slurmdb_association_rec_t *assoc_in,
				 slurmdb_qos_rec_t *qos_ptr,
				 uint16_t *limit_set_max_cpus,
				 uint16_t *limit_set_max_nodes,
				 uint16_t *limit_set_time, bool update_call);
/*
 * acct_policy_job_runnable - Determine of the specified job can execute
 *	right now or not depending upon accounting policy (e.g. running
 *	job limit for this association). If the association limits prevent
 *	the job from ever running (lowered limits since job submissin),
 *	then cancel the job.
 */
extern bool acct_policy_job_runnable(struct job_record *job_ptr);

/*
 * acct_policy_update_pending_job - Make sure the limits imposed on a
 *	job on submission are correct after an update to a qos or
 *	association.  If the association/qos limits prevent
 *	the job from ever running (lowered limits since job submission),
 *	then cancel the job.
 */
extern int acct_policy_update_pending_job(struct job_record *job_ptr);

extern bool acct_policy_node_usable(struct job_record *job_ptr,
				    uint32_t used_cpus,
				    char *node_name, uint32_t node_cpus);


#endif /* !_HAVE_ACCT_POLICY_H */