/**
* @author Dinesh Manajipet, Vovoid Media Technologies - Copyright (C) 2012-2020
* @author Michael Kedl - Copyright (C) 2012-2020
* @see The GNU Public License (GPL)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/


#include "vsx_math_3d.h"
#include "vsx_param.h"
#include "vsx_module.h"

class vsx_external_program_module : public vsx_module
{
  vsx_module_param_string* param1;
  vsx_module_param_string* param2;
  vsx_module_param_int* param3;
  vsx_module_param_float* param4;
  vsx_module_param_float* param5;
  vsx_module_param_float* param6;
  vsx_module_param_string* result;

public:

  void module_info(vsx_module_info* info)
  {
    info->identifier = "system;external_program";
    info->description = "Passes string_arg,float1,float2,float3 to an external_program at max_times_per_second.";
    info->in_param_spec =
        "external_program:string,"
        "string_arg:string,"
        "max_times_per_sec:int,"
        "float1:float,"
        "float2:float,"
        "float3:float"
    ;
    info->out_param_spec = "result:string";
    info->component_class = "system";
  }

  void declare_params(vsx_module_param_list& in_parameters, vsx_module_param_list& out_parameters)
  {
    param1 = (vsx_module_param_string*)in_parameters.create(VSX_MODULE_PARAM_ID_STRING,"external_program");
    param2 = (vsx_module_param_string*)in_parameters.create(VSX_MODULE_PARAM_ID_STRING,"string_arg");
    param3 = (vsx_module_param_int*)in_parameters.create(VSX_MODULE_PARAM_ID_INT,"max_times_per_sec");
    param4 = (vsx_module_param_float*)in_parameters.create(VSX_MODULE_PARAM_ID_FLOAT,"float1");
    param5 = (vsx_module_param_float*)in_parameters.create(VSX_MODULE_PARAM_ID_FLOAT,"float2");
    param6 = (vsx_module_param_float*)in_parameters.create(VSX_MODULE_PARAM_ID_FLOAT,"float3");

    result = (vsx_module_param_string*)out_parameters.create(VSX_MODULE_PARAM_ID_STRING,"result");

    param1->set("");
    param2->set("");
    param3->set(1);
    param4->set(0);
    param5->set(0);
    param6->set(0);
    result->set("none");
    loading_done = true;
  }


  void run()
  {
    static char exec_cmd[1000];
    const char *cmd;
    const char *sarg;
    cmd = param1->get().c_str();
    sarg = param2->get().c_str();
    sprintf(exec_cmd,"%s %s %f %f %f",cmd,sarg,param4->get(),param5->get(),param6->get());
    system(exec_cmd);
    result->set("done");
  }

};
