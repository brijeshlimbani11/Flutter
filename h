protected void mergePdfButton_Click(object sender, EventArgs e)
{
    // Create the merge result PDF document
    Document mergeResultPdfDocument = new Document();

    // Automatically close the merged documents when the document resulted after merge is closed
    mergeResultPdfDocument.AutoCloseAppendedDocs = true;

    // Set license key received after purchase to use the converter in licensed mode
    // Leave it not set to use the converter in demo mode
    mergeResultPdfDocument.LicenseKey = "fvDh8eDx4fHg4P/h8eLg/+Dj/+jo6Og=";

    try
    {
        // The documents to merge must remain opened until the PDF document resulted after merge is saved
        // The merged documents can be automatically closed when the document resulted after merge is closed
        // if the AutoCloseAppendedDocs property of the PDF document resulted after merge is set on true like
        // in this demo applcation

        // Load the first PDF document to merge
        string firstPdfFilePath = Server.MapPath("~/DemoAppFiles/Input/PDF_Files/Merge_Before_Conversion.pdf");
        Document firstPdfDocumentToMerge = new Document(firstPdfFilePath);
        // Merge the first PDF document
        mergeResultPdfDocument.AppendDocument(firstPdfDocumentToMerge);

        // Load the second PDF document to merge
        string secondPdfFilePath = Server.MapPath("~/DemoAppFiles/Input/PDF_Files/Merge_After_Conversion.pdf");
        Document secondPdfDocumentToMerge = new Document(secondPdfFilePath);
        // Merge the second PDF document
        mergeResultPdfDocument.AppendDocument(secondPdfDocumentToMerge);

        // Save the merge result PDF document in a memory buffer
        byte[] outPdfBuffer = mergeResultPdfDocument.Save();

        // Send the PDF as response to browser

        // Set response content type
        Response.AddHeader("Content-Type", "application/pdf");

        // Instruct the browser to open the PDF file as an attachment or inline
        Response.AddHeader("Content-Disposition", String.Format("attachment; filename=Merge_PDF.pdf; size={0}", outPdfBuffer.Length.ToString()));

        // Write the PDF document buffer to HTTP response
        Response.BinaryWrite(outPdfBuffer);

        // End the HTTP response and stop the current page processing
        Response.End();
    }
    finally
    {
        // Close the PDF document resulted after merge
        // When the AutoCloseAppendedDocs property is true the merged PDF documents will also be closed
        mergeResultPdfDocument.Close();
    }
}











<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="YourPageName.aspx.cs" Inherits="YourNamespace.YourPageName" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>HTML to PDF Conversion</title>
    <style>
        .form-container {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #f9f9f9;
        }
        .form-group {
            margin-bottom: 15px;
        }
        .form-group label {
            display: block;
            font-weight: bold;
        }
        .form-group input[type="file"] {
            margin-top: 5px;
        }
        .form-group input[type="submit"] {
            padding: 10px 20px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        .form-group input[type="submit"]:hover {
            background-color: #45a049;
        }
        .file-names {
            margin-top: 10px;
        }
        .file-names ul {
            list-style-type: none;
            padding: 0;
        }
        .file-names ul li {
            margin-bottom: 5px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server" enctype="multipart/form-data">
        <div class="form-container">
            <div class="form-group">
                <label for="fileUpload">Upload HTML files:</label>
                <asp:FileUpload ID="fileUpload" runat="server" CssClass="form-control" Multiple="true" />
            </div>
            <div class="form-group">
                <asp:Button ID="convertToPdfButton" runat="server" Text="Convert to PDF" OnClick="convertToPdfButton_Click" CssClass="btn btn-primary" />
            </div>
            <div class="file-names" runat="server" id="fileNamesDiv">
                <ul>
                    <!-- File names will be dynamically added here -->
                </ul>
            </div>
        </div>
    </form>
</body>
</html>






using System;
using System.IO;
using System.Web.UI;

namespace YourNamespace
{
    public partial class DownloadPage : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindPdfFiles();
            }
        }

        private void BindPdfFiles()
        {
            string pdfDirectory = Server.MapPath("~/PDFFiles/");
            string[] pdfFiles = Directory.GetFiles(pdfDirectory, "*.pdf");

            foreach (string pdfFile in pdfFiles)
            {
                string fileName = Path.GetFileName(pdfFile);
                string pdfUrl = ResolveUrl("~/PDFFiles/" + fileName);

                pdfFilesRepeater.DataSource = pdfFiles;
                pdfFilesRepeater.DataBind();
            }
        }
    }
}





<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DownloadPage.aspx.cs" Inherits="YourNamespace.DownloadPage" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Download PDF Files</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h2>Download PDF Files</h2>
            <asp:Repeater ID="pdfFilesRepeater" runat="server">
                <ItemTemplate>
                    <div>
                        <a href='<%# Eval("PdfUrl") %>' target="_blank"><%# Eval("FileName") %></a>
                    </div>
                </ItemTemplate>
            </asp:Repeater>
        </div>
    </form>
</body>
</html>



using System;
using System.Drawing;
using System.IO;
using System.Web;
using Winnovative.WnvHtmlConvert;

protected void convertToPdfButton_Click(object sender, EventArgs e)
{
    // Check if files were uploaded
    if (fileUpload.HasFiles)
    {
        // Create a PDF document for each uploaded file
        foreach (HttpPostedFile uploadedFile in fileUpload.PostedFiles)
        {
            // Ensure the file is of HTML format
            if (Path.GetExtension(uploadedFile.FileName).ToLower() == ".html")
            {
                // Create the PDF document
                Document pdfDocument = new Document();

                // Set license key received after purchase to use the converter in licensed mode
                // Leave it not set to use the converter in demo mode
                pdfDocument.LicenseKey = "fvDh8eDx4fHg4P/h8eLg/+Dj/+jo6Og=";

                // Create a PDF page
                PdfPage pdfPage = pdfDocument.AddPage();

                try
                {
                    // Create the HTML to PDF element
                    HtmlToPdfElement htmlToPdfElement = new HtmlToPdfElement(0, 0, uploadedFile.InputStream, "");

                    // Optionally set a delay before conversion to allow asynchronous scripts to finish
                    htmlToPdfElement.ConversionDelay = 2;

                    // Add the HTML to PDF document
                    pdfPage.AddElement(htmlToPdfElement);

                    // Generate a unique file name for the PDF
                    string fileName = Path.GetFileNameWithoutExtension(uploadedFile.FileName) + ".pdf";

                    // Write the PDF document to a file
                    pdfDocument.Save(Path.Combine(Server.MapPath("~/PDFFiles"), fileName));
                }
                finally
                {
                    // Close the PDF document
                    pdfDocument.Close();
                }
            }
        }

        // Provide a download link for the generated PDF files
        Response.Redirect("~/DownloadPage.aspx");
    }
    else
    {
        // No files uploaded, provide appropriate message
        // For example:
        // errorLabel.Text = "Please upload at least one HTML file.";
    }
}




<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="YourPageName.aspx.cs" Inherits="YourNamespace.YourPageName" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>HTML to PDF Conversion</title>
    <style>
        .form-container {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #f9f9f9;
        }
        .form-group {
            margin-bottom: 15px;
        }
        .form-group label {
            display: block;
            font-weight: bold;
        }
        .form-group input[type="text"], .form-group input[type="url"] {
            width: 100%;
            padding: 10px;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
        }
        .form-group input[type="file"] {
            margin-top: 5px;
        }
        .form-group button {
            padding: 10px 20px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        .form-group button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <div class="form-container">
            <div class="form-group">
                <asp:FileUpload ID="fileUpload" runat="server" CssClass="form-control" AllowMultiple="true" />
            </div>
            <div class="form-group">
                <asp:CheckBox ID="startNewPageCheckBox" runat="server" Text="Start New Page" />
            </div>
            <div class="form-group">
                <asp:Button ID="convertToPdfButton" runat="server" Text="Convert to PDF" OnClick="convertToPdfButton_Click" CssClass="btn btn-primary" />
            </div>
        </div>
    </form>
</body>
</html>