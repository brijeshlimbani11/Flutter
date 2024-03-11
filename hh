<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Form</title>
</head>

<body>
    <table>
        <tr>
            <td style="width: 100%;">
                <input type="radio" id="RBLProjecttype_0" name="RBLProjecttype" value="000000" checked>
                <label for="RBLProjecttype_0">Normal CRF Print</label>
                <input type="radio" id="RBLProjecttype_1" name="RBLProjecttype" value="1">
                <label for="RBLProjecttype_1">Annotated CRF Print</label>
            </td>
        </tr>

        <tr>
            <td style="width: 100%;">
                <table width="100%" align="center">
                    <tr>
                        <td class="LabelText" style="text-align: left; width: 25%;">Project No.* : </td>
                        <td class="LabelText" colspan="" style="text-align: left; width: 70%;">
                            <input type="text" id="txtproject" class="textBox" style="margin-top: 14px;">
                            &nbsp;
                            <button id="btnSetProject" style="display: none">Project</button>
                            <input type="hidden" id="HProjectId">
                            <div id="AutoCompleteExtender1" class="autocomplete_list"></div>
                            <div id="pnlProjectList" style="max-height: 200px; overflow: auto; overflow-x: hidden"></div>
                        </td>
                        <td align="center" class="Label" style="width: 5%;">
                            <div id="lockdtl" style="display: none;">
                                <img src="images/UnFreeze.jpg" id="ImageLockUnlock" alt="Lock">
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
                        <td style="text-align: left; width: 12%;" class="LabelText">Period* :</td>
                        <td style="text-align: left; width: 28%;" class="LabelText">
                            <select id="ddlPeriod" onchange="fnSubjectSelection();"></select>
                        </td>
                        <td style="text-align: right; width: 25%;" class="LabelText">Activity Type* :</td>
                        <td style="text-align: left; width: 15%;" class="LabelText">
                            <select id="ddlActivityType">
                                <option selected>Select Activity</option>
                                <option>Generic Activities</option>
                                <option>Subject Specific Activities</option>
                            </select>
                        </td>
                    </tr>

                    <tr>
                        <td style="text-align: left;" class="LabelText">Subject :</td>
                        <td colspan="3" style="text-align: left;" class="LabelText">
                            <select id="ddlSubject" multiple="multiple" style="width: 11%;"></select>
                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            <label for="ddlPrinttype">Print Type* :</label>
                            <select id="ddlPrinttype" class="LabelText" style="text-align: right;">
                                <option selected>Select Print Type</option>
                                <option>Draft</option>
                                <option>Final</option>
                            </select>
                        </td>
                    </tr>

                    <tr>
                        <td style="text-align: left; width: 12%;" class="LabelText">Size* :</td>
                        <td style="text-align: left; width: 28%;" class="LabelText">
                            <select id="ddlOrientation" onchange="fnSubjectSelection();" style="width: 100%;">
                                <option value="A4">A4</option>
                                <option value="Letter">Letter</option>
                            </select>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
</body>

</html>





<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title></title>
    <link href="App_Themes/StyleBlue/StyleBlue.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" href="App_Themes/CDMS.css" />
    <link rel="stylesheet" type="text/css" href="App_Themes/jquery.multiselect.css" />
    <link rel="stylesheet" href="Script/jquery-ui-1.10.4.custom.min.css">

    <style>
        /* Your CSS styles here */
    </style>
</head>
<body>
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
                                            <input type="radio" id="RBLselect_0" name="RBLselect" value="0" checked>
                                            <label for="RBLselect_0">Download</label>
                                            <input type="radio" id="RBLselect_1" name="RBLselect" value="1">
                                            <label for="RBLselect_1" style="padding-left: 99px;">Preview</label>
                                        </td>
                                    </tr>
                                    <!-- Other rows similar to the one above -->
                                </table>
                            </fieldset>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>

    <!-- Scripts -->
    <script src="Script/jquery-2.1.0.min.js"></script>
    <script src="Script/jquery-ui-1.10.4.custom.min.js"></script>
    <script src="Script/jquery.dataTables.min.js"></script>
    <script src="Script/jquery.dragtable.min.js"></script>
    <script src="Script/FixedHeader.min.js"></script>
    <script src="Script/General.js"></script>
    <script src="Script/AutoComplete.js"></script>
    <script src="Script/jquery.dataTables.plugins.js"></script>
    <script src="Script/jquery.multiselect.min.js"></script>
    <script src="Script/jquery.multiselect.js"></script>
    <script src="Script/jquery.dataTables.js"></script>
    <script>
        // Your JavaScript code here
    </script>
</body>
</html>
