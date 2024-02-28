	public bool GetSetProject()
	{

		string wStr = string.Empty;
		string ParaMeters = string.Empty;
		DataSet Ds = new DataSet();

		try
		{
			ParaMeters = Convert.ToString(this.Session[GeneralModule.S_UserID]);
			if (!objHelp.Proc_SetProjectMatrix(ParaMeters,ref Ds,ref eStr_Retu))
			{
				objCommon.ShowAlert("Error While Proc_SetProjectMatrix", this.Page);
			}
			if (Ds.Tables.Count != 0 && Ds.Tables[0].Rows.Count > 0 && !string.IsNullOrEmpty(Convert.ToString(Ds.Tables[0].Rows[0]["WorkSpaceId"])) && !string.IsNullOrEmpty(Convert.ToString(Ds.Tables[0].Rows[0]["ProjectNo"])))
			{
				Session.Add(GeneralModule.S_ProjectName, Ds.Tables[0].Rows[0]["ProjectNo"]);
				Session.Add(GeneralModule.S_ProjectId, Ds.Tables[0].Rows[0]["WorkSpaceId"]);
			}
			return true;
		}
		catch (Exception ex)
		{
            this.ShowErrorMessage(ex.Message, "Eroor While getSetProject....", ex);
            objCommon.ShowAlert("Eroor While getSetProject....", this.Page);
			return false;
		}

	}
