<%@ Page Title="" Language="C#" MasterPageFile="~/ECTDMasterPage_New.master" AutoEventWireup="false"
    CodeFile="frmCRFPrint_New.aspx.cs" Inherits="frmCRFPrint_New" %>

<%@ Register Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" TagPrefix="cc1" %>
<asp:Content ID="Content1" ContentPlaceHolderID="CPHLAMBDA" runat="Server">
    <link href="App_Themes/StyleBlue/StyleBlue.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" href="App_Themes/CDMS.css" />
    <link rel="stylesheet" type="text/css" href="App_Themes/jquery.multiselect.css" />

    <script src="Script/jquery-2.1.0.min.js" type="text/javascript"></script>
    <script src="Script/jquery-ui-1.10.4.custom.min.js" type="text/javascript"></script>
    <script src="Script/jquery.dataTables.min.js" type="text/javascript"></script>
    <script src="Script/jquery.dragtable.min.js" type="text/javascript"></script>
    <script src="Script/FixedHeader.min.js" type="text/javascript"></script>
    <script src="Script/General.js" language="javascript" type="text/javascript"></script>
    <script type="text/javascript" src="Script/AutoComplete.js"></script>
    <script src="Script/jquery.dataTables.plugins.js" type="text/javascript"></script>
    <script src="Script/jquery.multiselect.min.js"></script>
    <script src="Script/jquery.multiselect.js"></script>
    <script src="Script/jquery.dataTables.js" type="text/javascript"></script>

    <style type="text/css">
        .FieldSetBox {
            border: #aaaaaa 1px solid;
            z-index: 0px;
            border-radius: 4px;
        }

        .textBox {
            color: Black !important;
            font-family: Delicious, sans-serif !important;
            font-size: 12px !important;
            width: 100%;
        }

        .Multiselect {
            color: #555;
            line-height: 165%;
        }

        .ui-multiselect {
            max-height: 35px;
            /*overflow: auto;*/
            overflow-x: hidden;
            white-space: nowrap;
        }

        .ui-multiselect-menu {
            width: 200px !important;
            max-height: 100px!important;
            font-size: 0.8em !important;
            overflow: auto;
        }

            .ui-multiselect-menu span {
                vertical-align: top;
            }

        .ui-menu .ui-menu-item a {
            font-size: 11px !important;
            text-align: left !important;
        }

        .ui-multiselect-checkboxes {
            overflow-y: visible !important;
        }

            .ui-multiselect-checkboxes li ul li {
                list-style: none !important;
                clear: both;
                font-size: 2.0em;
                padding-right: 3px;
            }

            .ui-multiselect-checkboxes ui-helper-reset {
                width: 500px;
            }

        .ui-widget {
            font-size: 1.0em;
        }

        .table1 {
            font-family: 'Times New Roman' !important;
        }
    </style>

    <asp:UpdatePanel runat="server" ID="UpPnlForCRFPrint">
        <ContentTemplate>

            <table width="100%" style="margin-top: 20px;">
                <tr>
                    <td style="width: 40%; vertical-align: top;">
                        <table width="100%">
                            <tr>
                                <td>

                                    <fieldset class="FieldSetBox" style="text-align: left; width: 99%; max-width: 99%">
                                        <legend class="LegendText" style="color: Black;">Project Details </legend>

                                        <table width="100%">
                                            <tr>
                                                <td style="width: 100%;">
                                                    <asp:RadioButtonList ID="RBLselect" runat="server" AutoPostBack="True"
                                                        RepeatDirection="Horizontal" Style="margin-left: 0px; vertical-align: middle">
                                                        <asp:ListItem Selected="true" Value="0"> Download</asp:ListItem>
                                                        <asp:ListItem Value="1" style="padding-left: 99px;"> Preview</asp:ListItem>
                                                    </asp:RadioButtonList>
                                                </td>
                                            </tr>
                                            <tr>
                                                <td style="width: 100%;">
                                                    <asp:RadioButtonList ID="RBLProjecttype" runat="server" AutoPostBack="True"
                                                        RepeatDirection="Horizontal" Style="margin-left: 0px;">
                                                        <asp:ListItem Selected="true" Value="000000"> Normal CRF Print</asp:ListItem>
                                                        <asp:ListItem Value="1" style="padding-left: 55px;"> Annotated CRF Print</asp:ListItem>
                                                    </asp:RadioButtonList>
                                                </td>
                                            </tr>

                                            <tr>
                                                <td style="width: 100%;">
                                                    <table width="100%" align="center">

                                                        <tr>
                                                            <td class="LabelText" style="text-align: left; width: 25%;">Project No.* : </td>
                                                            <td class="LabelText" colspan="" style="text-align: left; width: 70%;">
                                                                <asp:TextBox ID="txtproject" runat="server" CssClass="textBox" onkeydown="return (event.keyCode!=13)" Style="margin-top: 14px;"></asp:TextBox>
                                                                &nbsp;
                                                                <asp:Button ID="btnSetProject" runat="server" OnClick="btnSetProject_Click" onkeydown="return (event.keyCode!=13)" Style="display: none" Text=" Project" />
                                                                <asp:HiddenField ID="HProjectId" runat="server" />
                                                               
                                                                <cc1:AutoCompleteExtender ID="AutoCompleteExtender1" runat="server" BehaviorID="AutoCompleteExtender1" 
                                                                    CompletionListCssClass="autocomplete_list" CompletionListElementID="pnlProjectList" 
                                                                    CompletionListHighlightedItemCssClass="autocomplete_highlighted_listitem" 
                                                                    CompletionListItemCssClass="autocomplete_listitem" MinimumPrefixLength="1" 
                                                                    OnClientItemSelected="OnSelected" OnClientShowing="ClientPopulated" 
                                                                    ServiceMethod="GetMyProjectCompletionList_dossier1" 
                                                                     TargetControlID="txtProject" UseContextKey="True">
                                                                     </cc1:AutoCompleteExtender>  

                                                                     <%--<cc1:AutoCompleteExtender ServiceMethod="GetMyProjectCompletionList_dossier1" MinimumPrefixLength="1"  
                                                                                          UseContextKey="True"          ID="AutoCompleteExtender1"    CompletionInterval="10" EnableCaching="false" CompletionSetCount="1" TargetControlID="txtproject"  
                                                                                                        runat="server" FirstRowSelected="false">  --%>
                                                                               
                                                               <%-- </cc1:AutoCompleteExtender>--%>
                                                                <asp:Panel ID="pnlProjectList" runat="server" Style="max-height: 200px; overflow: auto; overflow-x: hidden" />
                                                            </td>
                                                            <td align="center" class="Label" style="width: 5%;">
                                                                <div id="lockdtl" runat="server" style="display: none;">
                                                                    <img src="images/UnFreeze.jpg" id="ImageLockUnlock" runat="server" alt="Lock" />
                                                                </div>
                                                            </td>
                                                        </tr>
                                                    </table>
                                                </td>
                                            </tr>

                                            <tr>
                                                <td style="width: 100%;">
                                                    <table width="100%" align="center">
                                                        <tr>
                                                            <td style="text-align: left; width: 12%;" class="LabelText">Period* : 
                                                            </td>
                                                            <td style="text-align: left; width: 28%;" class="LabelText">
                                                                <asp:DropDownList ID="ddlPeriod" runat="server" AutoPostBack="true" Width="100%" onchange=" fnSubjectSelection();">
                                                                </asp:DropDownList>
                                                            </td>

                                                            <td style="text-align: right; width: 25%;" class="LabelText">Activity Type* :
                                                            </td>
                                                            <td style="text-align: left; width: 15%;" class="LabelText">
                                                                <asp:DropDownList ID="ddlActivityType" runat="server" AutoPostBack="true">
                                                                    <asp:ListItem Selected="True">Select Activity </asp:ListItem>
                                                                    <asp:ListItem>Generic Activities</asp:ListItem>
                                                                    <asp:ListItem>Subject Specific Activities</asp:ListItem>
                                                                </asp:DropDownList>
                                                            </td>

                                                        </tr>

                                                        <tr>
                                                            <td style="text-align: left;" class="LabelText">Subject :</td>

                                                            <td colspan="3" style="text-align: left;" class="LabelText">
                                                                <asp:DropDownList runat="server" ID="ddlSubject" multiple="multiple" Width="11%">
                                                                </asp:DropDownList>

                                                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                                            <asp:Label ID="Label1" runat="server">Print Type*  : </asp:Label>
                                                                <asp:DropDownList ID="ddlPrinttype" runat="server" class="LabelText" Style="text-align: right;">
                                                                    <asp:ListItem Selected="True">Select Print Type </asp:ListItem>
                                                                    <asp:ListItem>Draft</asp:ListItem>
                                                                    <asp:ListItem>Final</asp:ListItem>
                                                                </asp:DropDownList>

                                                            </td>
                                                        </tr>

                                                        <tr>
                                                            <td style="text-align: left; width: 12%;" class="LabelText">Size* : 
                                                            </td>
                                                            <td style="text-align: left; width: 28%;" class="LabelText">
                                                                <asp:DropDownList ID="ddlOrientation" runat="server" AutoPostBack="true" Width="100%">
                                                                    <asp:ListItem Value="A4">A4</asp:ListItem>
                                                                    <asp:ListItem Value="Letter">Letter</asp:ListItem>
                                                                </asp:DropDownList>
                                                            </td>

                                                        </tr>

                                                    </table>

                                                </td>

                                            </tr>

                                            <tr>

                                                <td class="LabelText" style="text-align: center; width: 100%;">

                                                    <asp:UpdatePanel ID="UPGrid" runat="server" RenderMode="Inline" UpdateMode="Conditional">

                                                        <ContentTemplate>

                                                            <div runat="server" id="divActivity" style="padding-top: 1%; width: 98%; display: none">

                                                                <fieldset class="FieldSetBox" id="FieldActivity" runat="server" style="text-align: left; width: 98%; max-width: 98%;">
                                                                    <legend class="LegendText" style="color: Black;">Acitivity </legend>
                                                                    <table width="100%">

                                                                        <tr>
                                                                            <td align="center" style="width: 100%;">
                                                                                <asp:Button ID="btnRearrangeActivity" runat="server" Text="Rearrange" CssClass="btn btnnew"
                                                                                    Style="font-size: 12px !important; display: none;" ToolTip="Rearrange" OnClientClick=" fnSubjectSelection();" />

                                                                            </td>
                                                                        </tr>

                                                                        <tr>

                                                                            <td align="center" style="width: 100%;">
                                                                                <asp:GridView ID="gvwActivity" AutoGenerateColumns="false" runat="server" Width="100%">

                                                                                    <Columns>

                                                                                        <asp:TemplateField>
                                                                                            <HeaderTemplate>
                                                                                                <input type="checkbox" id="chkSelectAll" name="chkSelectAll" onclick="SelectAllActivity(this, 'gvwActivity')" />
                                                                                                <asp:Label ID="Label1" runat="server" Text="Select All"></asp:Label>
                                                                                            </HeaderTemplate>
                                                                                            <ItemTemplate>
                                                                                                <input type="checkbox" runat="server" id="chkSelect" name="chkSelect" onclick="ChildActivityRow(this, 'gvwActivity')" />
                                                                                            </ItemTemplate>
                                                                                            <ItemStyle HorizontalAlign="Center" VerticalAlign="Middle" />

                                                                                        </asp:TemplateField>

                                                                                        <asp:BoundField HeaderText="Sr.No">
                                                                                            <ItemStyle HorizontalAlign="Center" VerticalAlign="Middle" />
                                                                                        </asp:BoundField>

                                                                                        <asp:BoundField DataField="iNodeId" HeaderText="NodeId" />

                                                                                        <asp:BoundField DataField="ChildActivityWithParent&Period" HeaderText="Activity Description" />

                                                                                        <asp:TemplateField HeaderText="Re-arrange">
                                                                                            <ItemTemplate>
                                                                                                <asp:Image ID="imgbtnRearrange" runat="server" ImageUrl="~/Images/Drag.png" ToolTip="Drag to Rearrange" CssClass="HandleParent" />
                                                                                            </ItemTemplate>
                                                                                            <ItemStyle HorizontalAlign="Center" VerticalAlign="Middle" />
                                                                                        </asp:TemplateField>

                                                                                    </Columns>

                                                                                </asp:GridView>
                                                                            </td>

                                                                        </tr>

                                                                    </table>
                                                                </fieldset>

                                                            </div>

                                                        </ContentTemplate>

                                                        <Triggers>

                                                            <asp:AsyncPostBackTrigger ControlID="ddlActivityType" EventName="SelectedIndexChanged" />
                                                            <asp:AsyncPostBackTrigger ControlID="btnRearrangeActivity" EventName="Click" />

                                                        </Triggers>

                                                    </asp:UpdatePanel>

                                                </td>

                                                <asp:HiddenField ID="HFGV_Activity" runat="server" />
                                            </tr>

                                            <tr>

                                                <td class="LabelText" style="text-align: center; width: 100%;">

                                                    <asp:UpdatePanel ID="UpdatePanel1" runat="server" RenderMode="Inline" UpdateMode="Conditional">

                                                        <ContentTemplate>

                                                            <div runat="server" id="divReport" style="padding-top: 1%; width: 98%; display: none">

                                                                <fieldset id="fieldReport" runat="server" class="FieldSetBox" style="text-align: left; width: 98%; max-width: 98%;">
                                                                    <legend class="LegendText" style="color: Black;">Report Type </legend>

                                                                    <table width="100%">

                                                                        <tr>
                                                                            <td align="center" style="width: 100%;">
                                                                                <asp:Button ID="btnRearrangeReport" runat="server" Text="Rearrange" CssClass="btn btnnew"
                                                                                    Style="font-size: 12px !important; display: none" ToolTip="Rearrange" OnClientClick=" fnSubjectSelection();" />

                                                                            </td>
                                                                        </tr>

                                                                        <tr>

                                                                            <td align="center" style="width: 100%;">
                                                                                <asp:GridView ID="gvwReportType" AutoGenerateColumns="false" runat="server">

                                                                                    <Columns>

                                                                                        <asp:TemplateField>
                                                                                            <HeaderTemplate>
                                                                                                <input type="checkbox" id="chkSelectAll" name="chkSelectAll" onclick="SelectAllReport(this, 'gvwReportType')" />
                                                                                                <asp:Label ID="Label1" runat="server" Text="Select All"></asp:Label>
                                                                                            </HeaderTemplate>
                                                                                            <ItemTemplate>
                                                                                                <input type="checkbox" runat="server" id="chkSelect" name="chkSelect" onclick="ChildReportRow(this, 'gvwActivity')" />
                                                                                            </ItemTemplate>
                                                                                            <ItemStyle HorizontalAlign="Center" VerticalAlign="Middle" />

                                                                                        </asp:TemplateField>

                                                                                        <asp:BoundField HeaderText="Sr.No">
                                                                                            <ItemStyle HorizontalAlign="Center" VerticalAlign="Middle" />
                                                                                        </asp:BoundField>

                                                                                        <asp:BoundField DataField="vReportId" HeaderText="ReportId" />

                                                                                        <asp:BoundField DataField="iNodeId" HeaderText="NodeId" />

                                                                                        <asp:BoundField DataField="vReportDesc" HeaderText="Report Description" />

                                                                                        <asp:TemplateField HeaderText="Re-arrange">
                                                                                            <ItemTemplate>
                                                                                                <asp:Image ID="imgbtnRearrange" runat="server" ImageUrl="~/Images/Drag.png" ToolTip="Drag to Rearrange" CssClass="HandleReport" />
                                                                                            </ItemTemplate>
                                                                                            <ItemStyle HorizontalAlign="Center" VerticalAlign="Middle" />
                                                                                        </asp:TemplateField>
                                                                                         <asp:BoundField DataField="vReportType" HeaderText="Report vReportType" />
                                                                                    </Columns>

                                                                                </asp:GridView>
                                                                            </td>

                                                                        </tr>
                                                                    </table>

                                                                </fieldset>


                                                            </div>
                                                        </ContentTemplate>
                                                        <Triggers>
                                                            <asp:AsyncPostBackTrigger ControlID="ddlActivityType" EventName="SelectedIndexChanged" />
                                                            <asp:AsyncPostBackTrigger ControlID="btnRearrangeReport" EventName="Click" />
                                                        </Triggers>
                                                    </asp:UpdatePanel>
                                                </td>
                                                <asp:HiddenField ID="HFGV_Report" runat="server" />
                                            </tr>
                                            <tr>
                                                <td>
                                                    <div id="dvheadershow" runat="server" style="margin-top: 5px; display: none;">
                                                        <fieldset id="fieldheader" runat="server" class="FieldSetBox" style="text-align: left; width: 98%; max-width: 98%;">
                                                            <legend class="LegendText" style="color: Black;">Exclude from header </legend>
                                                            <table>
                                                                <tr>
                                                                    <td>
                                                                        <asp:CheckBox ID="chkinitial" runat="server" Text="Subject Initials" />
                                                                    </td>
                                                                    <td style="padding-left: 30px;">Upload Logo
                                                                    </td>
                                                                </tr>
                                                                <tr>
                                                                    <td>
                                                                        <asp:CheckBox ID="chkprotocolno" runat="server" Text="Protocol No" />
                                                                    </td>
                                                                    <td style="padding-left: 30px;">
                                                                        <asp:FileUpload ID="fusponsorlogo" runat="server" Width="200px" onchange="validate_fileupload(this);" />
                                                                        <label for="validation" style="color: red;">*Only JPEG file allowed</label>
                                                                    </td>
                                                                </tr>
                                                            </table>
                                                            <%--<div id="dvcheckbox" runat="server" align="left">
                                                            <asp:CheckBox ID="chkinitial" runat="server" Text="Subject Initial not print" />
                                                            <asp:CheckBox ID="chkprotocolno" runat="server" Text="ProtocolNo  not print" />
                                                        </div>
                                                        <div id="dvfileupload" runat="server" style="margin-top: 5px" align="left">
                                                            Select Sponsor Logo:
                                                                        <asp:FileUpload ID="fusponsorlogo" runat="server" width="200px" onchange="validate_fileupload(this);"/>
                                                            <label for="validation" style="color:red;">*Only JPEG file allowed</label>
                                                            <%--<p style="color:red"></p>--%>
                                                        </fieldset>
                                                    </div>
                                                </td>
                                            </tr>

                                            <%--  <tr>
                                                <td>
                                                    <div id="divECG" runat="server" style="margin-top: 5px;">
                                                        <fieldset id="Fieldset1" runat="server" class="FieldSetBox" style="text-align: left; width: 98%; max-width: 96%;">
                                                            <legend class="LegendText" style="color: Black;">Include ECG</legend>
                                                            <table>
                                                                <tr>
                                                                    <td style="padding-left: 13px;" colspan="2">
                                                                        <asp:CheckBox runat="server" Text="ECG" ID="chkECG2" Style="display: block" />
                                                                    </td>
                                                                </tr>

                                                            </table>

                                                        </fieldset>
                                                    </div>
                                                </td>
                                            </tr>--%>

                                            <tr>
                                                <td>
                                                    <table>
                                                        <tr>
                                                            <td style="padding-left: 13px;">
                                                                <asp:CheckBox runat="server" ID="chkDataType" />
                                                                <asp:Label runat="server" ID="lblDataType" Text="With Data Type ?" Width="105px"></asp:Label>
                                                            </td>
                                                            <td>
                                                                <asp:CheckBox runat="server" TextAlign="Right" Text="Sub Activity Wise" ID="chkSubactivityWise" Style="display: block" />
                                                            </td>
                                                        </tr>
                                                        <%--<tr>
                                                            <td style="padding-left: 13px;" colspan="2">
                                                                <asp:CheckBox runat="server" Text="ECG" ID="chkECG" Style="display: block" />
                                                            </td>
                                                        </tr>--%>
                                                    </table>
                                                </td>
                                            </tr>
                                            <tr>
                                                <td style="text-align: center;">
                                                    <asp:Button ID="btnGo" runat="server" CssClass="btn btngo"
                                                        OnClientClick="return validationBlankProjectAndActivity();" />

                                                    <asp:Button ID="btnCancel" runat="server" CssClass="btn btncancel" Text="Cancel" />

                                                    <asp:Button ID="btnExit" runat="server" Text="Exit" CssClass="btn btnexit"
                                                        CausesValidation="False" OnClientClick="return Exit(this);" />

                                                </td>

                                            </tr>

                                        </table>

                                    </fieldset>

                                </td>
                            </tr>
                        </table>
                    </td>

                    <td style="width: 60%; padding-left: 1.5%; vertical-align: top;">

                        <table width="100%" cellpadding="0" cellspaceing="0">

                            <tr>

                                <td>

                                    <fieldset class="FieldSetBox" style="text-align: left; width: 97%; max-width: 97%">
                                        <legend class="LegendText" style="color: Black;">CRF Structure</legend>

                                        <table width="100%" cellpadding="3">

                                            <tr>

                                                <td style="float: right;">
                                                    <asp:Button ID="BtnGeneratePdf" runat="server"
                                                        Style="font-size: 12px !important; display: block;"
                                                        OnClientClick="return validateForm();" CssClass="btn btnpdf" />
                                                    <asp:HiddenField ID="HFHeaderLabel" runat="server" />
                                                    <asp:HiddenField ID="HFHeaderPDF" runat="server" />
                                                </td>

                                            </tr>

                                            <tr>

                                                <td>

                                                    <div style="text-align: center; overflow: auto; height: 600px; display: none;" id="HeaderLabel"
                                                        runat="server" align="center">
                                                        <table style="width: 100%" align="center" id="MainContentTable" runat="server" class="table1">
                                                            <tbody>
                                                                <tr align="center">
                                                                    <td align="center" width="100%" colspan="3">
                                                                        <asp:UpdatePanel ID="UpPlaceHolder" runat="server" UpdateMode="Conditional" RenderMode="Inline">
                                                                            <ContentTemplate>
                                                                                <asp:Panel ID="PnlPlaceMedex" runat="server" Width="100%" ScrollBars="Auto">
                                                                                    <asp:PlaceHolder ID="PlaceMedEx" runat="server" EnableViewState="true"></asp:PlaceHolder>
                                                                                </asp:Panel>
                                                                            </ContentTemplate>
                                                                        </asp:UpdatePanel>
                                                                    </td>
                                                                </tr>
                                                            </tbody>
                                                        </table>
                                                    </div>

                                                    <div id="divHeaderPDF" style="display: none;" runat="server" align="left" enableviewstate="false">
                                                        <table runat="server" id="tbldivheader" style="padding: 2px; margin: auto; border: solid 1px black; width: 100%; font-family: 'Times New Roman' !Important; font-size: 12px;"
                                                            align="left">
                                                            <tr>
                                                                <td>
                                                                    <table>
                                                                        <tr>
                                                                            <td colspan="4" style="vertical-align: top;">
                                                                                <table>
                                                                                    <tr>
                                                                                        <%--<td style="vertical-align: top; font-size: 12px; font-family: 'Times New Roman' !Important;"><%=ConfigurationManager.AppSettings("ClientName") %>
																																				
                                                                                        </td>--%>
                                                                                        <td style="vertical-align: top; font-size: 12px; font-family: 'Times New Roman' !Important;">
                                                                                            <%=Session["ClientName"]%> 																																				
                                                                                        </td>
                                                                                    </tr>
                                                                                    <tr>
                                                                                        <td style="vertical-align: top; font-size: 12px; font-family: 'Times New Roman' !Important;">
                                                                                            <span id="spnBaBe" runat="server"></span>
                                                                                        </td>
                                                                                    </tr>
                                                                                    <tr>
                                                                                        <td style="vertical-align: bottom; font-size: 12px; font-weight: bold !important; font-family: 'Times New Roman' !Important; text-align: right">CASE REPORT FORM
                                                                                        </td>
                                                                                    </tr>
                                                                                </table>
                                                                            </td>
                                                                        </tr>
                                                                        <tr>
                                                                            <td align="right" style="font-family: 'Times New Roman' !Important; font-size: 12px;">Project No. :
                                                                            </td>
                                                                            <td style="border: thin solid #000000; font-family: 'Times New Roman' !Important; font-size: 12px;">
                                                                                <asp:Label ID="lblProjectNo" runat="server" Text="_" EnableViewState="false"></asp:Label>
                                                                            </td>
                                                                            <td id="tdSiteName" align="right" runat="server" enableviewstate="false" style="font-family: 'Times New Roman' !Important; font-size: 12px;">
                                                                                <span id="SpnSite" runat="server" enableviewstate="false">Site Id: </span>
                                                                            </td>
                                                                            <td id="tdSiteId" runat="server" style="border: thin solid #000000; font-family: 'Times New Roman' !Important; font-size: 12px;" enableviewstate="false">
                                                                                <asp:Label ID="lblSiteNo" runat="server" Text="_" EnableViewState="false"></asp:Label>
                                                                            </td>
                                                                        </tr>
                                                                        <tr id="trProtocol" runat="server" enableviewstate="false" style="font-family: 'Times New Roman' !Important; font-size: 12px;">
                                                                            <td align="right" style="font-family: 'Times New Roman' !Important;">
                                                                                <span id="Span1" runat="server" enableviewstate="false">Protocol No: </span>
                                                                            </td>
                                                                            <td style="border: thin solid #000000; font-family: 'Times New Roman' !Important; font-size: 12px;">
                                                                                <asp:Label ID="LblProtocol" runat="server" Text="_" EnableViewState="false"></asp:Label>
                                                                            </td>
                                                                        </tr>
                                                                        <tr id="trsubjectno" runat="server">
                                                                            <td align="right" style="font-family: 'Times New Roman' !Important; font-size: 12px;">
                                                                                <span id="SpnSubject" runat="server" enableviewstate="false">Subject No: </span>
                                                                            </td>
                                                                            <td style="border: thin solid #000000; font-family: 'Times New Roman' !Important; font-size: 12px;">
                                                                                <asp:Label ID="lblSubjectNo" runat="server" Text="_" EnableViewState="false"></asp:Label>
                                                                            </td>
                                                                            <td align="right" style="font-family: 'Times New Roman' !Important; font-size: 12px;">
                                                                                <span id="SpnSubjectInit" runat="server" enableviewstate="false">Subject Initials:
                                                                                </span>
                                                                            </td>
                                                                            <td style="border: thin solid #000000; font-family: 'Times New Roman' !Important; font-size: 12px;">
                                                                                <asp:Label ID="lblSubjectName" runat="server" Text="_" EnableViewState="false"></asp:Label>
                                                                            </td>
                                                                        </tr>
                                                                    </table>
                                                                </td>
                                                                <td align="right">
                                                                    <img alt="" runat="server" id="Imgsponsor" enableviewstate="false" style="width: 120px; height: 120px; display: none;" />
                                                                </td>
                                                                <td valign="top">
                                                                    <img alt="" runat="server" id="ImgLogo" enableviewstate="false" style="width: 120px; height: 120px;" />
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </div>

                                                </td>

                                            </tr>

                                        </table>

                                    </fieldset>

                                </td>

                            </tr>

                        </table>

                    </td>

                    <asp:HiddenField ID="hdnSubSelection" runat="server" />
                    <asp:HiddenField ID="hdnLock" runat="server" />
                </tr>
            </table>

        </ContentTemplate>
        <Triggers>

            <asp:AsyncPostBackTrigger ControlID="RBLProjecttype" EventName="SelectedIndexChanged" />
            <asp:AsyncPostBackTrigger ControlID="RBLselect" EventName="SelectedIndexChanged" />
            <asp:PostBackTrigger ControlID="BtnGeneratePdf" />
            <asp:PostBackTrigger ControlID="btnGo" />

        </Triggers>
    </asp:UpdatePanel>
    <script src="Script/jquery-ui.js" type="text/javascript"></script>
    <script src="Script/jquery.multiselect.min.js" type="text/javascript"></script>
    <script type="text/javascript">
        var ArrSub = [];
        function pageLoad() {
            fnApplyDtAddReport();
            fnApplyDtAddActivity();
            if ($("#<%= ddlSubject.ClientID%>")) {
                fnApplySelectSubjectType();

            }


        }

        function fnApplySelectSubjectType() {
            fnDeletePreviousMultiselect();

            $("#<%= ddlSubject.ClientID%>").multiselect({
                noneSelectedText: "--Select Subject--",
                minWidth: "auto",
                selectedList: 0,
                click: function (event, ui) {
                    if (ui.checked == true)
                        ArrSub.push("'" + ui.value + "'");
                    else if (ui.checked == false) {
                        if ($.inArray("'" + ui.value + "'", ArrSub) >= 0)
                            ArrSub.splice(ArrSub.indexOf("'" + ui.value + "'"), 1);
                    }
                    if (ArrSub.length > 0) {
                        $("#ctl00_CPHLAMBDA_lblDataType").css("display", "none");
                        $("#ctl00_CPHLAMBDA_chkDataType").css("display", "none");
                    }
                    else {
                        $("#ctl00_CPHLAMBDA_lblDataType").css("display", "");
                        $("#ctl00_CPHLAMBDA_chkDataType").css("display", "");
                    }

                },
                checkAll: function (event, ui) {
                    ArrSub = [];
                    for (var i = 0; i < event.target.options.length; i++) {
                        ArrSub.push("'" + $(event.target.options[i]).val() + "'");
                    }

                    $("#ctl00_CPHLAMBDA_lblDataType").css("display", "none");
                    $("#ctl00_CPHLAMBDA_chkDataType").css("display", "none");


                },
                uncheckAll: function (event, ui) {
                    ArrSub = [];
                    $("#ctl00_CPHLAMBDA_lblDataType").css("display", "");
                    $("#ctl00_CPHLAMBDA_chkDataType").css("display", "");
                }
            });

            $("#<%= ddlSubject.ClientID%>").multiselect("refresh");
            var CheckedCheckBox = document.getElementById('<%= hdnSubSelection.ClientID %>').value
            if (CheckedCheckBox != "") {

                CheckedCheckBox = CheckedCheckBox.split(',');
                for (i = 0; i <= CheckedCheckBox.length - 1; i++) {
                    $("#<%= ddlSubject.ClientID %>").multiselect("widget").find(".ui-multiselect-checkboxes.ui-helper-reset").find("input[value=" + CheckedCheckBox[i] + "]").attr("checked", "checked");

                }
                $('#<%= ddlSubject.ClientID%>').multiselect("update");
            }
        }

        function fnSubjectSelection() {
            var subtypes = [];
            document.getElementById('<%= hdnSubSelection.ClientID%>').value = "";
            for (i = 0; i < $(".ui-multiselect-checkboxes.ui-helper-reset input[name='multiselect_ctl00_CPHLAMBDA_ddlSubject']:checked").length; i++) {
                subtypes.push("'" + $(".ui-multiselect-checkboxes.ui-helper-reset input[name='multiselect_ctl00_CPHLAMBDA_ddlSubject']:checked").eq(i).attr("value") + "'");
            }
            document.getElementById('<%= hdnSubSelection.ClientID %>').value = subtypes;
            return true;
        }

        function fnDeletePreviousMultiselect() {
            // if ($("ul[class*='ui-multiselect']").length > 1) {
            $('#aspnetForm').nextUntil('ul[id*="ui-id"]').not('#shadow').remove();
            $('#aspnetForm').next().not('#shadow').remove();
            //} 
        }

        function validateForm() {
            document.getElementById('<%= HFHeaderLabel.ClientID %>').value = document.getElementById('<%=HeaderLabel.ClientID %>').innerHTML;
            document.getElementById('<%= HFHeaderPDF.ClientID %>').value = document.getElementById('<%=divHeaderPDF.ClientID %>').innerHTML;
            return true;
        }

        function ClientPopulated(sender, e) {
            ProjectClientShowing('AutoCompleteExtender1', $get('<%= txtproject.ClientID %>'));
        }

        function OnSelected(sender, e) {
            ProjectOnItemSelected(e.get_value(), $get('<%= txtproject.ClientID %>'),
            $get('<%= HProjectId.ClientID %>'), document.getElementById('<%= btnSetProject.ClientID %>'));
            fnDeletePreviousMultiselect();
        }

        function validationBlankProjectAndActivity() {


            if (document.getElementById('<%= txtproject.ClientID%>').value == "" || document.getElementById('<%= HProjectId.ClientID%>').value == "") {
                msgalert("Please Select Project Name/Request Id !");
                document.getElementById('<%= txtproject.ClientID%>').focus();
                return false;

            }
            else if (document.getElementById('<%= ddlActivityType.ClientID%>').selectedIndex === 0) {
                msgalert('Please Select Activity Type !');
                document.getElementById('<%= ddlActivityType.ClientID%>').focus();
                return false;
            }
            else if (document.getElementById('<%= ddlPrinttype.ClientID%>').selectedIndex === 0) {
                 msgalert('Please Select Print Type !');
                 document.getElementById('<%= ddlPrinttype.ClientID%>').focus();
               return false;
           }
           else if (document.getElementById('<%= ddlPrinttype.ClientID%>').selectedIndex == 2) {
                if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() != "--Select Subject--") {
                    if ($('#ctl00_CPHLAMBDA_ddlSubject').val().length > 0) {
                        if ($('#ctl00_CPHLAMBDA_hdnLock').val().toUpperCase() == "FALSE") {
                            msgalert('Project is in unlock stage. You cannot proceed !');
                            return false;
                        }
                    }
                }
            }
            else if (document.getElementById('ctl00_CPHLAMBDA_RBLselect_1').checked == true) {
                if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() != "--Select Subject--") {
                    if ($('#ctl00_CPHLAMBDA_ddlSubject').val().length > 10) {
                        msgalert('You can not select more than 10 subject !');
                        return false;
                    }
                }
            }
            //if ($('#ctl00_CPHLAMBDA_hdnLock').val().toUpperCase() == "TRUE") {
            //   //if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() == "--Select Subject--") {
            //  //    alert('Please Select Atleast 1 Subject');
            // //    return false;
            // //}
            //if (document.getElementById('<%= ddlActivityType.ClientID%>').selectedIndex == 2) {
            //   if ($('#ctl00_CPHLAMBDA_divReport').is(':visible') && $('input[id$="chkSelect"]:checked', '#<%=gvwReportType.ClientID%>').length <= 0) {
            //      alert('Please Select Atleast One Report Type.');
            //     return false;
            //}
            //}
            //        else {

            //          if ($('#ctl00_CPHLAMBDA_divActivity').is(':visible') && $('input[id$="chkSelect"]:checked', '#<%=gvwActivity.ClientID%>').length <= 0) {
            //            alert('Please Select Atleast One Activity.');
            //          return false;
            //    }

            //}
            //}
            //else {

            if (document.getElementById('<%= ddlActivityType.ClientID%>').selectedIndex === 2) { // Subject Specific Activityies

                if ($('#ctl00_CPHLAMBDA_divReport').is(':visible') && $('input[id$="chkSelect"]:checked', '#<%=gvwReportType.ClientID%>').length <= 0) {
                    msgalert('Please Select Atleast One Report Type !');
                    return false;
                }
                else {
                    var text = $('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase()

                    if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('CRF REPORT') >= 0) {
                        if ($('#ctl00_CPHLAMBDA_divActivity').is(':visible') && $('input[id$="chkSelect"]:checked', '#<%=gvwActivity.ClientID%>').length <= 0) {
                             msgalert('Please Select Atleast One Activity !');
                             return false;
                         }
                     }

                     if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('ECRF STATUS HISTORY REPORT') >= 0) {
                         if ($('#ctl00_CPHLAMBDA_divActivity').is(':visible') && $('input[id$="chkSelect"]:checked', '#<%=gvwActivity.ClientID%>').length <= 0) {
                           msgalert('Please Select Atleast One Activity !');
                           return false;
                       }
                   }
                   if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('ECRF DATA CHANGE STATUS REPORT') >= 0) {
                       if ($('#ctl00_CPHLAMBDA_divActivity').is(':visible') && $('input[id$="chkSelect"]:checked', '#<%=gvwActivity.ClientID%>').length <= 0) {
                            msgalert('Please Select Atleast One Activity !');
                            return false;
                        }
                    }

                    //if (($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('CRF REPORT') < 0) || ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('ECRF VERSION HISTORY REPORT') < 0)) {
                    //     if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() == "--Select Subject--") {
                    //         msgalert('Please Select Atleast 1 Subject !');
                    //         return false;
                    //     }
                    // }
                    // else {

                    if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length > 2) {
                        if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() == "--Select Subject--") {
                            msgalert('Please Select Atleast 1 Subject !');
                            return false;
                        }
                    }
                    else if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length <= 2) {
                        if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('CRF REPORT') >= 0) {
                            if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('ECRF VERSION HISTORY REPORT') >= 0) {
                            }
                            else {
                                if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length == 1) {
                                    if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('CRF REPORT') >= 0) {
                                        // Do Nothing
                                    }
                                    else if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('ECRF VERSION HISTORY REPORT') >= 0) {
                                        // Do Nothing
                                    }
                                    else {
                                        // if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length != 2) {
                                        if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() == "--Select Subject--") {
                                            msgalert('Please Select Atleast 1 Subject !');
                                            return false;
                                        }
                                    }
                                }
                                else {
                                    // if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length != 2) {
                                    if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() == "--Select Subject--") {
                                        msgalert('Please Select Atleast 1 Subject !');
                                        return false;
                                    }
                                }
                            }
                        }
                        else {
                            if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length == 1) {
                                if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('CRF REPORT') >= 0) {
                                    // Do Nothing
                                }
                                else if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('ECRF VERSION HISTORY REPORT') >= 0) {
                                    // Do Nothing
                                }
                                else {
                                    // if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length != 2) {
                                    if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() == "--Select Subject--") {
                                        msgalert('Please Select Atleast 1 Subject !');
                                        return false;
                                    }
                                }
                            }
                            else {
                                // if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length != 2) {
                                if ($('#ctl00_CPHLAMBDA_ddlSubject').next().children().eq(1).text() == "--Select Subject--") {
                                    msgalert('Please Select Atleast 1 Subject !');
                                    return false;
                                }
                            }

                        }
                    }

                    //}
                }
                if ($('#ctl00_CPHLAMBDA_divActivity').is(':visible') && $('input[id$="chkSelect"]:checked', '#<%=gvwActivity.ClientID%>').length > 0) {
                    //if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').closest('tr').find('td:eq(4)').text().toUpperCase().indexOf('CRF REPORT') < 0) {
                    //    msgalert('Please Select CRF Report Type !');
                    //    return false;
                    //}
                }

            }
            else {
                if ($('#ctl00_CPHLAMBDA_divActivity').is(':visible') && $('input[id$="chkSelect"]:checked', '#<%=gvwActivity.ClientID%>').length <= 0) {
                    msgalert('Please Select Atleast One Activity !');
                    return false;
                }
            }
            //}
            fnSubjectSelection();
            return true;
        }

        function getReportSequence() {
            var i = 1;
            var sequencedata = [];
            $('.SaveReport').each(function () {
                var ContentActivity = new Object();
                $(this).children("td:nth-child(2)").html(i)
                ContentActivity.iNodeId = $(this).children("td:nth-child(4)").html();
                sequencedata.push(ContentActivity);
                ContentActivity.iSeqNo = i;
                i = parseInt(i) + 1;

            });
            $('#<%= HFGV_Report.ClientID %>').val(JSON.stringify(sequencedata));
             $('#<%=btnRearrangeReport.ClientID%>').css('display', 'inline');
             $('#<%=BtnGeneratePdf.ClientID%>').css('display', 'none');
             $('input[id*="chkSelect"]', '#ctl00_CPHLAMBDA_gvwReportType').attr('disabled', 'disabled');
             $('input[id*="chkSelectAll"]', $get('ctl00_CPHLAMBDA_gvwReportType_wrapper')).attr('disabled', 'disabled')
             return true;
         }

         function fnApplyDtAddReport() {

             if ($get('<%= gvwReportType.ClientID %>') != null && $get('<%= gvwReportType.ClientID %>_wrapper') == null) {
                var oTab = $('#<%= gvwReportType.ClientID %>').prepend($('<thead>').append($('#<%= gvwReportType.ClientID %> tr:first'))).dataTable({
                    "bJQueryUI": true,
                    "sScrollY": '140px',
                    "bStateSave": false,
                    "bDestory": true,
                    "bPaginate": false,
                    "bInfo": true,
                    "bFilter": false,
                    "bSort": false,
                    "bRetrieve": true,
                    "bFooter": false,
                    "bAutoWidth": false,
                    "sDom": '<"H"lfr>t<"F"p>'

                });

                setTimeout(function () {
                    oTab.fnAdjustColumnSizing();
                    if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length > 0 || $('input[id$="chkSelectAll"]:checked', '#ctl00_CPHLAMBDA_gvwReportType_wrapper').length > 0) {

                        $('#<%=btnRearrangeReport.ClientID%>').css('display', 'none');

                        $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwReportType').removeClass("HandleReport");

                    }
                    $('#ctl00_CPHLAMBDA_gvwReportType_wrapper .dataTables_scrollHeadInner').css('width', '')
                    $('#ctl00_CPHLAMBDA_gvwReportType_wrapper .dataTables_scrollHeadInner table').css('width', '')
                    $('#ctl00_CPHLAMBDA_gvwReportType_wrapper .dataTables_scrollBody ').css('width', '')
                }, 5);

                $('#<%= gvwReportType.ClientID %> tbody').sortable({
                    handle: ".HandleReport",
                    activate: function (event, ui) {

                        $('.ui-sortable-helper').removeAttr('style');
                    },
                    deactivate: function (event, ui) {

                        getReportSequence();

                    },
                    stop: function (event, ui) {
                        if (ui.item.children("th").length != 0 || ui.item.children("td:nth-child(2)").html() == "&nbsp;") {
                            $(this).sortable("cancel");
                        }
                    }
                });
            }
        }

        function getActivitySequence() {
            var i = 1;
            var sequencedata = [];
            $('.SaveActivity').each(function () {
                var ContentActivity = new Object();
                $(this).children("td:nth-child(2)").html(i)
                ContentActivity.iNodeId = $(this).children("td:nth-child(3)").html();
                ContentActivity.iNodeNo = i;
                sequencedata.push(ContentActivity);
                i = parseInt(i) + 1;

            });
            $('#<%= HFGV_Activity.ClientID %>').val(JSON.stringify(sequencedata));
            $('#<%=btnRearrangeActivity.ClientID%>').css('display', 'inline');
            $('#<%=BtnGeneratePdf.ClientID%>').css('display', 'none');
            $('input[id*="chkSelect"]', '#ctl00_CPHLAMBDA_gvwActivity').attr('disabled', 'disabled');
            $('input[id*="chkSelectAll"]', $get('ctl00_CPHLAMBDA_gvwActivity_wrapper')).attr('disabled', 'disabled')
            return true;
        }

        function fnApplyDtAddActivity() {

            if ($get('<%= gvwActivity.ClientID %>') != null && $get('<%= gvwActivity.ClientID %>_wrapper') == null) {
                var oTab = $('#<%= gvwActivity.ClientID %>').prepend($('<thead>').append($('#<%= gvwActivity.ClientID %> tr:first'))).dataTable({
                    "bJQueryUI": true,
                    "sScrollY": '200px',
                    "bStateSave": false,
                    "bDestory": true,
                    "bPaginate": false,
                    "bInfo": true,
                    "bFilter": false,
                    "bSort": false,
                    "bRetrieve": true,
                    "bFooter": false,
                    "bAutoWidth": false,
                    "sDom": '<"H"lfr>t<"F"p>'

                });
                setTimeout(function () {
                    oTab.fnAdjustColumnSizing();
                    if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwActivity').length > 0 || $('input[id$="chkSelectAll"]:checked', '#ctl00_CPHLAMBDA_gvwActivity_wrapper').length > 0) {

                        $('#<%=btnRearrangeActivity.ClientID%>').css('display', 'none');

                        $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwActivity').removeClass("HandleParent");

                    }
                    //$('input[id*="chkSelect"]', $get('ctl00_CPHLAMBDA_gvwActivity')).removeAttr('checked');
                    $('#ctl00_CPHLAMBDA_gvwActivity_wrapper .dataTables_scrollHeadInner').css('width', '')
                    $('#ctl00_CPHLAMBDA_gvwActivity_wrapper .dataTables_scrollHeadInner table').css('width', '')
                    $('#ctl00_CPHLAMBDA_gvwActivity_wrapper .dataTables_scrollBody ').css('width', '')
                }, 5);

                $('#<%= gvwActivity.ClientID %> tbody').sortable({
                    handle: ".HandleParent",
                    activate: function (event, ui) {
                        $('.ui-sortable-helper').removeAttr('style');
                    },
                    deactivate: function (event, ui) {

                        getActivitySequence();


                    },
                    stop: function (event, ui) {
                        if (ui.item.children("th").length != 0 || ui.item.children("td:nth-child(2)").html() == "&nbsp;") {
                            $(this).sortable("cancel");
                        }
                    }
                });
            }
        }

        function SelectAllActivity(CheckBoxControl, Grid) {
            var subject = [];
            var Gvd = document.getElementById('<%=gvwActivity.ClientID %>');

            $('#<%=BtnGeneratePdf.ClientID%>').css('display', 'none');
            if ($('input[id$="chkSelectAll"]:checked', '#ctl00_CPHLAMBDA_gvwActivity_wrapper').length > 0) {

                $('#<%=btnRearrangeActivity.ClientID%>').css('display', 'none');

                $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwActivity').removeClass("HandleParent");

            }
            else {

                $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwActivity').addClass("HandleParent");
            }

            if (CheckBoxControl.checked == true) {
                var i;
                var Cell = 0;
                for (i = 0; i < document.forms[0].elements.length; i++) {
                    if ((document.forms[0].elements[i].type == 'checkbox') && (document.forms[0].elements[i].name.indexOf(Grid) > -1)) {
                        if (document.forms[0].elements[i].disabled == false) {
                            document.forms[0].elements[i].checked = true;
                            Cell += 1;
                        }
                    }
                }

            }
            else {
                var i;
                for (i = 0; i < document.forms[0].elements.length; i++) {
                    if ((document.forms[0].elements[i].type == 'checkbox') && (document.forms[0].elements[i].name.indexOf(Grid) > -1)) {
                        document.forms[0].elements[i].checked = false;
                    }
                }

            }
        }

        function ChildActivityRow(row, Grid) {

            var rownode = row.parentNode.parentNode;
            var subject = [];
            $('#<%=BtnGeneratePdf.ClientID%>').css('display', 'none');
            if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwActivity').length > 0 || $('input[id$="chkSelectAll"]:checked', '#ctl00_CPHLAMBDA_gvwActivity_wrapper').length > 0) {

                $('#<%=btnRearrangeActivity.ClientID%>').css('display', 'none');

                $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwActivity').removeClass("HandleParent");

            }
            else {

                $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwActivity').addClass("HandleParent");
            }

            if (row.checked == true) {
                subject.push(rownode.children[2].innerText);
            }
            else {
                var index = subject.indexOf(rownode.children[2].innerText);
                subject.splice(index, 1);
            }

            var Checkall = document.getElementById('chkSelectAll');
            var Gvd = document.getElementById('<%=gvwActivity.ClientID %>');
            j = 0;
            for (i = 0; i < document.forms[0].elements.length; i++) {

                if ((document.forms[0].elements[i].type == 'checkbox') && (document.forms[0].elements[i].name.indexOf(Grid) > -1)) {
                    j = j + 1;
                    if (document.forms[0].elements[i].checked == false) {
                        Checkall.checked = false;
                        break;
                    }
                    else if (document.forms[0].elements[i].checked == true) {
                        if (j == Gvd.rows.length - 2) {
                            Checkall.checked = true;
                        }
                    }
                }
            }
            return true;
        }

        function SelectAllReport(CheckBoxControl, Grid) {
            var subject = [];
            $('#<%=BtnGeneratePdf.ClientID%>').css('display', 'none');
            var Gvd = document.getElementById('<%=gvwReportType.ClientID %>');

            if ($('input[id$="chkSelectAll"]:checked', '#ctl00_CPHLAMBDA_gvwReportType_wrapper').length > 0) {

                $('#<%=btnRearrangeReport.ClientID%>').css('display', 'none');


                $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwReportType').removeClass("HandleReport");

            }
            else {

                $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwReportType').addClass("HandleReport");
            }
            if (CheckBoxControl.checked == true) {
                var i;
                var Cell = 0;
                for (i = 0; i < document.forms[0].elements.length; i++) {
                    if ((document.forms[0].elements[i].type == 'checkbox') && (document.forms[0].elements[i].name.indexOf(Grid) > -1)) {
                        if (document.forms[0].elements[i].disabled == false) {
                            document.forms[0].elements[i].checked = true;
                            Cell += 1;
                        }
                    }
                }

            }
            else {
                var i;
                for (i = 0; i < document.forms[0].elements.length; i++) {
                    if ((document.forms[0].elements[i].type == 'checkbox') && (document.forms[0].elements[i].name.indexOf(Grid) > -1)) {
                        document.forms[0].elements[i].checked = false;
                    }
                }

            }
        }

        function ChildReportRow(row, Grid) {
            var rownode = row.parentNode.parentNode;
            var subject = [];
            $('#<%=BtnGeneratePdf.ClientID%>').css('display', 'none');
            if ($('input[id$="chkSelect"]:checked', '#ctl00_CPHLAMBDA_gvwReportType').length > 0 || $('input[id$="chkSelectAll"]:checked', '#ctl00_CPHLAMBDA_gvwReportType_wrapper').length > 0) {

                $('#<%=btnRearrangeReport.ClientID%>').css('display', 'none');

                $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwReportType').removeClass("HandleReport");

            }
            else {

                $('img[id$="imgbtnRearrange"], #ctl00_CPHLAMBDA_gvwReportType').addClass("HandleReport");
            }

            if (row.checked == true) {
                subject.push(rownode.children[2].innerText);
            }
            else {
                var index = subject.indexOf(rownode.children[2].innerText);
                subject.splice(index, 1);
            }

            var Checkall = document.getElementById('chkSelectAll');
            var Gvd = document.getElementById('<%=gvwReportType.ClientID %>');
            j = 0;
            for (i = 0; i < document.forms[0].elements.length; i++) {

                if ((document.forms[0].elements[i].type == 'checkbox') && (document.forms[0].elements[i].name.indexOf(Grid) > -1)) {
                    j = j + 1;
                    if (document.forms[0].elements[i].checked == false) {
                        Checkall.checked = false;
                        break;
                    }
                    else if (document.forms[0].elements[i].checked == true) {
                        if (j == Gvd.rows.length - 2) {
                            Checkall.checked = true;
                        }
                    }
                }
            }
            return true;
        }

        jQuery.browser = {};
        (function () {
            jQuery.browser.msie = false;
            jQuery.browser.version = 0;
            if (navigator.userAgent.match(/MSIE ([0-9]+)\./)) {
                jQuery.browser.msie = true;
                jQuery.browser.version = RegExp.$1;
            }
        })();


        function Exit(e) {
            msgConfirmDeleteAlert(null, "Are you sure, you want to exit the form ?", function (isConfirmed) {
                if (isConfirmed) {
                    parent.window.close();
                    __doPostBack(e.name, '');
                    return true;
                } else {

                    return false;
                }
            });
            return false;
        }

        function validate_fileupload(e) {
            var status = "";
            var allowed_extensions = new Array("jpg", "jpeg");
            var file_extension = e.value.split('.').pop();
            var FileName, FN, RemoveExt, FileLength;

            FileName = document.getElementById("ctl00_CPHLAMBDA_fusponsorlogo").value;
            var FileN = FileName.substring(FileName.lastIndexOf('\\') + 1)
            RemoveExt = FileN.split(".");
            FileLength = RemoveExt[0].length;

            for (var i = 0; i <= allowed_extensions.length; i++) {
                if (allowed_extensions[i] == file_extension) {
                    status = "Allow";
                    return true; // valid file extension
                }
            }
            if (status != "Allow") {
                msgalert("You can only select file like [ jpg - jpeg ] [ " + file_extension + " ] file is Not allow to upload !");

                document.getElementById("ctl00_CPHLAMBDA_fusponsorlogo").value = "";
                return false
            }
            return false;
        }
    </script>

</asp:Content>
