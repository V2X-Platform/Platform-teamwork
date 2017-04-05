#include "StdAfx.h"
#include "mt_create.h"
#include "base_create.h"


MT_CREATE::MT_CREATE(SCENARIO_PARA scenario_data,pair<double,double> sitevect[],complex<double> areavect[])
{

	basenum = scenario_data.basenum;             //基站数目
                                                 //
	MT_num = scenario_data.MT_num;
	mt_perline=scenario_data.mt_perline;

	ISD = scenario_data.ISD;

	site_vect = sitevect;

	//for Freeway case
    Freeway_arealength = 2*sys_ISD;
    Freeway_arealength = 59;

	Min_dist = scenario_data.Min_dist;
}


MT_CREATE::~MT_CREATE(void)
{
#ifdef DESTRUCT_MODE
	std::ofstream OUT_destruct("result/destruction.txt",ios::out|ios::app);
	OUT_destruct<<"MT_CREATE Destructing...\n";

	cout<<"MT_CREATE Destructing...\n";
#endif
}


//***************************************************************************************
//每个site内生成一个mt，中心site的mt位置随主函数的loop_index（形参loop_i）由内至外变化，其他site的mt随机
//***************************************************************************************
void MT_CREATE::Create_newmt(SCENARIO_PARA scenario_data,list<MT_INFO*> &mt_list, MT_INFO* mt_trace, int &mt_num,int &new_mtnum,int &mt_topnum,int mt_traceid,int simul_step,int loop_i)
{
	//cout<<"\n Create MT position ......"<<endl;

	if (loop_i==0 && simul_step == 0)
	{
		//at first step generate a certain number of MT
		new_mtnum = MT_num;
	}
	else
	{
		//MT arrival in the Possion process
		new_mtnum = 0;//possion_realvalue();
	}

	double rand_data_1;
	double rand_data;

	if( new_mtnum>0 )
	{
		//parameter struct
		MT_PARA mtpara;

		for(int i=0; i<new_mtnum; i++)
		{
			//user id
			mtpara.mtid = i+mt_topnum;

			mtpara.gen_time = simul_step*sys_tstep;

			//---- MT position generation ----
			//mtpara.position = Uniform_position(scenario);

			complex<double>ue_position=Uniform_position(scenario);
			mtpara.position=ue_position;

			int y=ue_position.imag();//此处的y是用来提出车辆位置的y坐标，一会用来判断方向的。//yty

			mtpara.y_sort=ue_position.imag();//yty
			mtpara.x_sort=ue_position.real();//yty


			//output the mt position

			//------------------------------------

			//--------生成属性：indoor or not-----
			//rand_data_1 = rand();
			//rand_data_1 = rand_data_1 / RAND_MAX;
			rand_data_1 = uniform_mtindoor();

			if(rand_data_1<P_in)
				mtpara.indoor = TRUE;
			else
				mtpara.indoor = FALSE;
			//------------------------------------

			//user velocity
			rand_data = 2*PI*uniform_mtv_direction()-PI;

			double v_init = sys_MT_vmean[scenario] / 3.6;
			if(scenario==SMa && mtpara.indoor == FALSE)
				v_init = sys_MT_vmean[scenario+1] / 3.6;

			if(scenario==UMi)
			{
				switch(y)
				{
				    case 37:
				    case 41:
				    case 45:
                        mtpara.velocity = v_init*complex<double>(1,0);
						break;
				    case 49:
				    case 53:
				    case 57:
					    mtpara.velocity = v_init*complex<double>(-1,0);
						break;
			    }
			}
			else
            mtpara.velocity = v_init*complex<double>(cos(rand_data),sin(rand_data));

			//user array direction
			if(scenario==UMi)
				switch(y)
				{
				    case 37:
				    case 41:
				    case 45:
						mtpara.array_directioin = 0;
					    break;
			        case 49:
				    case 53:
				    case 57:
					    mtpara.array_directioin = PI;
						break;
			     }
			else
				mtpara.array_directioin = 2*PI*uniform_mt_array()-PI;
			// New MT
			mt_list.push_back(new MT_INFO(scenario_data,mtpara));

			// find the trace MT
			if (mtpara.mtid== mt_traceid)
			{
				//mt_trace = *(mt_list.end()--);
				list<MT_INFO*>::iterator iter = mt_list.end();
				iter--;
				mt_trace = *iter;
			}
		}

		mt_num = mt_num+new_mtnum;

		mt_topnum = mt_topnum+new_mtnum;

#ifdef  MT_Position_DEBUG
		Output_mtposition(mt_list);
#endif
	}
	else //loop_i !=0 || simul_step != 0
	{
		if(simul_step == 0 || MT_Redrop_mode == TRUE)//重新生成所有用户的位置，indoor属性不变
		{
			//仅更新位置信息
			//list <MT_INFO*>::iterator  mt_ptr;
			//for(mt_ptr = mt_list.begin(); mt_ptr!=mt_list.end(); mt_ptr++)
			//{
			//	(*mt_ptr)->mt_position = Uniform_position(scenario);
			//}

			//更新用户位置及Indoor信息，清除其他信息
			MT_Redrop(mt_list);

#ifdef  MT_Position_DEBUG
			Output_mtposition(mt_list);
#endif
		}
	}

	mt_list.sort(Comp_MT_x());

	list<MT_INFO*>::iterator mt_ptr;

	int id_inline37=-1;
	int id_inline41=-1;
	int id_inline45=-1;
	int id_inline49=-1;
	int id_inline53=-1;
	int id_inline57=-1;
	int mt_y_sort;

	int total_37,total_41,total_45,total_49,total_53,total_57;


	for (mt_ptr = mt_list.begin(); mt_ptr != mt_list.end(); mt_ptr++)
	{
		mt_y_sort=(*mt_ptr)->y_sort;
		switch(mt_y_sort)
		{
		case(37):
			id_inline37++;
			(*mt_ptr)->id_inline=id_inline37;
			total_37=id_inline37+1;
			break;
		case(41):
			id_inline41++;
			(*mt_ptr)->id_inline=id_inline41;
			total_41=id_inline41+1;
			break;
		case(45):
			id_inline45++;
			(*mt_ptr)->id_inline=id_inline45;
			total_45=id_inline45+1;
			break;
		case(49):
			id_inline49++;
			(*mt_ptr)->id_inline=id_inline49;
			total_49=id_inline49+1;
			break;
		case(53):
			id_inline53++;
			(*mt_ptr)->id_inline=id_inline53;
			total_53=id_inline53+1;
			break;
		case(57):
			id_inline57++;
			(*mt_ptr)->id_inline=id_inline57;
			total_57=id_inline57+1;
			break;
		}
	}

	list<MT_INFO*>::iterator it = mt_list.begin();
	for (; it != mt_list.end(); it++)
	{
		mt_y_sort=(*it)->y_sort;
		switch(mt_y_sort)
		{
		case(37):
			(*mt_ptr)->total_inline=total_37;
			(*it)->Init_data_struct(scenario_data,total_37);
			break;

		case(41):
			(*mt_ptr)->total_inline=total_41;
			(*it)->Init_data_struct(scenario_data,total_41);
			break;

		case(45):
			(*mt_ptr)->total_inline=total_45;
			(*it)->Init_data_struct(scenario_data,total_45);
			break;

		case(49):
			(*mt_ptr)->total_inline=total_49;
			(*it)->Init_data_struct(scenario_data,total_49);
			break;

		case(53):
			(*mt_ptr)->total_inline=total_53;
			(*it)->Init_data_struct(scenario_data,total_53);
			break;

		case(57):
			(*mt_ptr)->total_inline=total_57;
			(*it)->Init_data_struct(scenario_data,total_57);
			break;

		}
	}

	Output_mtposition(mt_list);


}
void MT_CREATE::Create_newmt_YTY(SCENARIO_PARA scenario_data,list<MT_INFO*> &mt_list, MT_INFO* mt_trace, int &mt_num,int &new_mtnum,int &mt_topnum,int mt_traceid,int simul_step,int loop_i,int mt_perline,int nums_line)
{
	//cout<<"\n Create MT position ......"<<endl;

	if (loop_i==0 && simul_step == 0)
	{
		//at first step generate a certain number of MT
		new_mtnum = MT_num;

	}
	else
	{
		//MT arrival in the Possion process
		new_mtnum = 0;//possion_realvalue();
	}

	double rand_data_1;
	double rand_data;

	if( new_mtnum>0 )
	{
		//parameter struct
		MT_PARA mtpara;

		for(int i=0; i<new_mtnum; i++)
		{
			//user id
			mtpara.mtid = i+mt_topnum;

			//mt type
			mtpara.mttype = HTTP;

			//mt gennerate time
			mtpara.gen_time = simul_step*sys_tstep;

			//---- MT position generation ----
			//mtpara.position = Uniform_position(scenario);
			mtpara.line=i/mt_perline;

			complex<double>ue_position=Uniform_position_YTY(mtpara.line);
			mtpara.position=ue_position;

			int y=ue_position.imag();//此处的y是用来提出车辆位置的y坐标，一会用来判断方向的。//yty

			mtpara.y_sort=ue_position.imag();//yty
			mtpara.x_sort=ue_position.real();//yty


			//output the mt position

			//------------------------------------

			//--------生成属性：indoor or not-----
			//rand_data_1 = rand();
			//rand_data_1 = rand_data_1 / RAND_MAX;
			//rand_data_1 = uniform_mtindoor();

			/*if(rand_data_1<P_in)
				mtpara.indoor = TRUE;
			else
				mtpara.indoor = FALSE;
            */
			    mtpara.indoor = FALSE;//车联网用，没有室内情况
			//------------------------------------

			//user velocity
			rand_data = 2*PI*uniform_mtv_direction()-PI;

			double v_init = sys_MT_vmean[scenario] / 3.6;
			if(scenario==SMa && mtpara.indoor == FALSE)
				v_init = sys_MT_vmean[scenario+1] / 3.6;

			if(scenario==UMi)
			{
				if(mtpara.line<3)
					{
						mtpara.velocity = v_init*complex<double>(1,0);
				        mtpara.array_directioin = 0;
				    }
				else
					{
						mtpara.velocity = v_init*complex<double>(-1,0);
				        mtpara.array_directioin = PI;
				    }
				/*switch(y)
				{
				    case 37:
				    case 41:
				    case 45:
                        mtpara.velocity = v_init*complex<double>(1,0);
						break;
				    case 49:
				    case 53:
				    case 57:
					    mtpara.velocity = v_init*complex<double>(-1,0);
						break;
			    }*/
			}
			else
            {
				mtpara.velocity = v_init*complex<double>(cos(rand_data),sin(rand_data));
			    mtpara.array_directioin = 2*PI*uniform_mt_array()-PI;//user array direction
			}

			//user array direction
			/*if(scenario==UMi)
				switch(y)
				{
				    case 37:
				    case 41:
				    case 45:
						mtpara.array_directioin = 0;
					    break;
			        case 49:
				    case 53:
				    case 57:
					    mtpara.array_directioin = PI;
						break;
			     }
			else
				mtpara.array_directioin = 2*PI*uniform_mt_array()-PI;
			*/
			// New MT
			mt_list.push_back(new MT_INFO(scenario_data,mtpara));

			// find the trace MT
			if (mtpara.mtid== mt_traceid)
			{
				//mt_trace = *(mt_list.end()--);
				list<MT_INFO*>::iterator iter = mt_list.end();
				iter--;
				mt_trace = *iter;
			}
		}

		mt_num = mt_num+new_mtnum;

		mt_topnum = mt_topnum+new_mtnum;

#ifdef  MT_Position_DEBUG
		Output_mtposition(mt_list);
#endif
	}
	else //loop_i !=0 || simul_step != 0
	{
		if(simul_step == 0 || MT_Redrop_mode == TRUE)//重新生成所有用户的位置，indoor属性不变
		{
			//仅更新位置信息
			//list <MT_INFO*>::iterator  mt_ptr;
			//for(mt_ptr = mt_list.begin(); mt_ptr!=mt_list.end(); mt_ptr++)
			//{
			//	(*mt_ptr)->mt_position = Uniform_position(scenario);
			//}

			//更新用户位置及Indoor信息，清除其他信息
			MT_Redrop(mt_list);

#ifdef  MT_Position_DEBUG
			Output_mtposition(mt_list);
#endif
		}
	}

	mt_list.sort(Comp_MT_x());

	list<MT_INFO*>::iterator mt_ptr;
	list<MT_INFO*>::iterator it;

	int id_inline37=-1;
	int id_inline41=-1;
	int id_inline45=-1;
	int id_inline49=-1;
	int id_inline53=-1;
	int id_inline57=-1;
	int mt_y_sort;

	int total_37,total_41,total_45,total_49,total_53,total_57;


	for (mt_ptr = mt_list.begin(); mt_ptr != mt_list.end(); mt_ptr++)
	{
		mt_y_sort=(*mt_ptr)->y_sort;
		switch(mt_y_sort)
		{
		case(37):
			id_inline37++;
			(*mt_ptr)->id_inline=id_inline37;
			total_37=id_inline37+1;
			break;
		case(41):
			id_inline41++;
			(*mt_ptr)->id_inline=id_inline41;
			total_41=id_inline41+1;
			break;
		case(45):
			id_inline45++;
			(*mt_ptr)->id_inline=id_inline45;
			total_45=id_inline45+1;
			break;
		case(49):
			id_inline49++;
			(*mt_ptr)->id_inline=id_inline49;
			total_49=id_inline49+1;
			break;
		case(53):
			id_inline53++;
			(*mt_ptr)->id_inline=id_inline53;
			total_53=id_inline53+1;
			break;
		case(57):
			id_inline57++;
			(*mt_ptr)->id_inline=id_inline57;
			total_57=id_inline57+1;
			break;
		}
	}


	for (it=mt_list.begin(); it != mt_list.end(); it++)
	{
		mt_y_sort=(*it)->y_sort;
		switch(mt_y_sort)
		{
		case(37):
			(*it)->total_inline=total_37;
			(*it)->Init_data_struct(scenario_data,total_37);
			break;

		case(41):
			(*it)->total_inline=total_41;
			(*it)->Init_data_struct(scenario_data,total_41);
			break;

		case(45):
			(*it)->total_inline=total_45;
			(*it)->Init_data_struct(scenario_data,total_45);
			break;

		case(49):
			(*it)->total_inline=total_49;
			(*it)->Init_data_struct(scenario_data,total_49);
			break;

		case(53):
			(*it)->total_inline=total_53;
			(*it)->Init_data_struct(scenario_data,total_53);
			break;

		case(57):
			(*it)->total_inline=total_57;
			(*it)->Init_data_struct(scenario_data,total_57);
			break;

		}
	}

	Output_mtposition(mt_list);


}

void MT_CREATE::MT_Redrop(list<MT_INFO*> &mt_list)//added 20091226 重撒用户位置及Indoor信息，清除其他信息
{
	list <MT_INFO*>::iterator  mt_ptr;

	for(mt_ptr = mt_list.begin(); mt_ptr!=mt_list.end(); mt_ptr++)
	{
		(*mt_ptr)->mt_position = Uniform_position(scenario);

		//--------重新生成属性：indoor or not-----
		double rand_data_1 = uniform_mtindoor();

		if(rand_data_1<P_in)
			(*mt_ptr)->Indoor = TRUE;
		else
			(*mt_ptr)->Indoor = FALSE;

		//重新生成用户移动方向及天线阵列方向
		double rand_data =  2*PI*uniform_mtv_direction()-PI;
		double v_init = sys_MT_vmean[scenario] / 3.6;
		if(scenario==SMa && (*mt_ptr)->Indoor == FALSE)
			v_init = sys_MT_vmean[scenario+1] / 3.6;

		(*mt_ptr)->mt_velocity = v_init*complex<double>(cos(rand_data),sin(rand_data));

		//user array direction
		(*mt_ptr)->mt_arraydirection = 2*PI*uniform_mt_array()-PI;

		//--------------------清除用户的其他信息----------------------------
		(*mt_ptr)->Clear_MT_status();

	}
}
complex<double>  MT_CREATE::Uniform_position(int scenario)
{
	//Position Generation,Uniformly distributed in the research area

	complex<double> temp_pos;

		double temp_dist_1, temp_dist_2, temp_x, temp_y;
		double x_coordinate;
		double y_coordinate;
	switch(scenario)
	{
	case InH:

		/*double temp_dist_1, temp_dist_2, temp_x, temp_y;
		double x_coordinate;
		double y_coordinate;*/

		do
		{
			//temp_x = rand();
			//temp_x = temp_x / RAND_MAX;
			temp_x = uniform_mtpos();

			//x_coordinate = temp_x * UMi_arealength - UMi_arealength;

			x_coordinate = temp_x * 50 - 25;

			//temp_y = rand();
			//temp_y = temp_y / RAND_MAX;
			temp_y = uniform_mtpos();

			y_coordinate = temp_y * UMi_arealength - UMi_arealength;

			temp_pos = complex<double>(x_coordinate,y_coordinate);

			temp_dist_1 = abs(temp_pos-site_vect[0]);

			temp_dist_2 = abs(temp_pos-site_vect[1]);
		}
		while(temp_dist_1<Min_dist || temp_dist_2<Min_dist);

		break;

	case UMi:                                                 //车联网相应修改



		do
		{
			//temp_x = rand();
			//temp_x = temp_x / RAND_MAX;
			temp_x = uniform_mtpos();

			//x_coordinate = temp_x * UMi_arealength - UMi_arealength/2;
			x_coordinate = temp_x * 250 ;

			//temp_y = rand();
			//temp_y = temp_y / RAND_MAX;
			temp_y = rand()%6;

			y_coordinate = temp_y * 4 +37;    //设置在车道中心进行行驶，车道宽4米，RSU在y=0处，RSU距离车道35m，那么6车道分别为35+4*x。

			temp_pos = complex<double>(x_coordinate,y_coordinate);

			temp_dist_1 = abs(temp_pos-site_vect[0]);

			temp_dist_2 = abs(temp_pos-site_vect[1]);
		}
		while(temp_dist_1<Min_dist || temp_dist_2<Min_dist);

	break;                                                    //车联网相应修改完毕


	default:                     // Other Senarios including UMi,UMa,RMa,SMa

		complex<double> E_vect;

		//srand((unsigned)time( NULL ));

		//随机选择移动台所在site,cell和section
		int site_index = rand() % bp_basenum;

		//int cell_index = rand() % cellnum_psite;

		int sect_index = rand() % 6;

		//----------------------生成在一个正三角形内均匀分布的点---------------------
		do
		{
			double r1 = R_max * uniform_mtpos();//rand() / RAND_MAX;
			double r2 = R_max * uniform_mtpos();//rand() / RAND_MAX;
			double temp;

			if(r1+r2>R_max)
			{
				temp = r1;
				r1 = R_max - r2;
				r2 = R_max - temp;
			}

			E_vect = r1 * complex<double>(cos(PI/6),sin(PI/6)) + r2 * complex<double>(cos(PI/2),sin(PI/2));

		}
		while(abs(E_vect)<Min_dist);//re-drop within minimun distance
		//--------------------------------------------------------------------------*/

		E_vect = E_vect * complex<double>(cos(PI*sect_index/3),sin(PI*sect_index/3));//rotate

		temp_pos = site_vect[site_index] + E_vect;//在area内的位置
	}

	return temp_pos;
}

complex<double>  MT_CREATE::Uniform_position_YTY(int line)
{
	//Position Generation,Uniformly distributed in the research area

	complex<double> temp_pos;

		double temp_dist_1, temp_dist_2, temp_x, temp_y;
		double x_coordinate;
		double y_coordinate;

		//do
		{
			temp_x = uniform_mtpos();


			x_coordinate = temp_x * 1732 ;

			y_coordinate = line * 4 +37;    //设置在车道中心进行行驶，车道宽4米，RSU在y=0处，RSU距离车道35m，那么6车道分别为35+4*x。

			temp_pos = complex<double>(x_coordinate,y_coordinate);

			//temp_dist_1 = abs(temp_pos-site_vect[0]);//此句话是计算与天线距离的，等到v2c时再用吧。

			//temp_dist_2 = abs(temp_pos-site_vect[1]);//同上；
		}
		//while(temp_dist_1<Min_dist || temp_dist_2<Min_dist);


	return temp_pos;
}

void MT_CREATE::Output_mtposition(list<MT_INFO*> &mt_list)
{

	MT_PARA mtpara;

	list<MT_INFO*> ::iterator mt_ptr;


	std::ofstream OUT_MTPOS("result/mtposition.txt",ios::out|ios::app);

	int id_inline;
	//std::ofstream OUT_XSORT("result/xsort.txt",ios::out|ios::app);

	//OUT<<"position = [ "<<endl;

    for(mt_ptr = mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
	{
		complex<double> mt_pos;
		//complex<double> xsort;

		mt_pos = (*mt_ptr)->Get_mtpos();

		id_inline= (*mt_ptr)->id_inline;
		//xsort=(*mt_ptr)-> Get_xsort();



		OUT_MTPOS<<mt_pos.real()/*<<"\t"<<mt_pos.imag()<<"\t"<<id_inline*/<<endl;
		//OUT_XSORT<<xsort<<endl;
	}

	//OUT<<"];"<<endl;

	OUT_MTPOS.close();

}






