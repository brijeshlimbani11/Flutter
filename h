<%@ Page Language="C#" AutoEventWireup="true" CodeFile="GeneratePdf.aspx.cs" Inherits="GeneratePdf" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Button ID="btnGeneratePdf" runat="server" Text="Generate PDF" OnClick="btnGeneratePdf_Click" />
        </div>
    </form>
</body>
</html>






using Spire.Pdf;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;
using System.IO;

public partial class GeneratePdf : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
    }

    protected void btnGeneratePdf_Click(object sender, EventArgs e)
    {
        // Create a PDF document
        PdfDocument doc = new PdfDocument();
        doc.PageSettings.Size = PdfPageSize.A4;

        // Reset the default margins to 0
        doc.PageSettings.Margins = new PdfMargins(0);

        // Create a PdfMargins object, the parameters indicate the page margins you want to set
        PdfMargins margins = new PdfMargins(60, 60, 60, 60);

        // Create a header template with content and apply it to page template
        doc.Template.Top = CreateHeaderTemplate(doc, margins);

        // Apply blank templates to other parts of page template
        doc.Template.Bottom = new PdfPageTemplateElement(doc.PageSettings.Size.Width, margins.Bottom);
        doc.Template.Left = new PdfPageTemplateElement(margins.Left, doc.PageSettings.Size.Height);
        doc.Template.Right = new PdfPageTemplateElement(margins.Right, doc.PageSettings.Size.Height);

        // Save the file to a MemoryStream
        MemoryStream stream = new MemoryStream();
        doc.SaveToStream(stream);
        stream.Position = 0;

        // Send the PDF file to the client as a downloadable file
        Response.Clear();
        Response.ContentType = "application/pdf";
        Response.AppendHeader("Content-Disposition", "attachment; filename=PdfHeader.pdf");
        Response.BinaryWrite(stream.ToArray());
        Response.End();
    }

    private PdfPageTemplateElement CreateHeaderTemplate(PdfDocument doc, PdfMargins margins)
    {
        // Get page size
        SizeF pageSize = doc.PageSettings.Size;

        // Create a PdfPageTemplateElement object as header space
        PdfPageTemplateElement headerSpace = new PdfPageTemplateElement(pageSize.Width, margins.Top);
        headerSpace.Foreground = false;

        // Declare two float variables
        float x = margins.Left;
        float y = 0;

        // Draw image in header space
        PdfImage headerImage = PdfImage.FromFile(Server.MapPath("logo.png"));
        float width = headerImage.Width / 3;
        float height = headerImage.Height / 3;
        headerSpace.Graphics.DrawImage(headerImage, x, margins.Top - height - 2, width, height);

        // Draw line in header space
        PdfPen pen = new PdfPen(PdfBrushes.Gray, 1);
        headerSpace.Graphics.DrawLine(pen, x, y + margins.Top - 2, pageSize.Width - x, y + margins.Top - 2);

        // Draw text in header space
        PdfTrueTypeFont font = new PdfTrueTypeFont(new Font("Impact", 25f, FontStyle.Bold));
        PdfStringFormat format = new PdfStringFormat(PdfTextAlignment.Left);
        String headerText = "HEADER TEXT";
        SizeF size = font.MeasureString(headerText, format);
        headerSpace.Graphics.DrawString(headerText, font, PdfBrushes.Gray, pageSize.Width - x - size.Width - 2, margins.Top - (size.Height + 5), format);

        // Return headerSpace
        return headerSpace;
    }
}






using Spire.Pdf;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;


namespace AddPDFHeader
{
    class Program
    {
        static void Main(string[] args)
        {
            //create a PDF document
            PdfDocument doc = new PdfDocument();
            doc.PageSettings.Size = PdfPageSize.A4;

            //reset the default margins to 0
            doc.PageSettings.Margins = new PdfMargins(0);

            //create a PdfMargins object, the parameters indicate the page margins you want to set
            PdfMargins margins = new PdfMargins(60, 60, 60, 60);

            //create a header template with content and apply it to page template
            doc.Template.Top = CreateHeaderTemplate(doc, margins);

            //apply blank templates to other parts of page template
            doc.Template.Bottom = new PdfPageTemplateElement(doc.PageSettings.Size.Width, margins.Bottom);
            doc.Template.Left = new PdfPageTemplateElement(margins.Left, doc.PageSettings.Size.Height);
            doc.Template.Right = new PdfPageTemplateElement(margins.Right, doc.PageSettings.Size.Height);

            //save the file
            doc.SaveToFile("PdfHeader.pdf");
        }
        static PdfPageTemplateElement CreateHeaderTemplate(PdfDocument doc, PdfMargins margins)
        {
            //get page size
            SizeF pageSize = doc.PageSettings.Size;

            //create a PdfPageTemplateElement object as header space
            PdfPageTemplateElement headerSpace = new PdfPageTemplateElement(pageSize.Width, margins.Top);
            headerSpace.Foreground = false;

            //declare two float variables
            float x = margins.Left;
            float y = 0;

            //draw image in header space 
            PdfImage headerImage = PdfImage.FromFile("logo.png");
            float width = headerImage.Width / 3;
            float height = headerImage.Height / 3;
            headerSpace.Graphics.DrawImage(headerImage, x, margins.Top - height - 2, width, height);

            //draw line in header space
            PdfPen pen = new PdfPen(PdfBrushes.Gray, 1);
            headerSpace.Graphics.DrawLine(pen, x, y + margins.Top - 2, pageSize.Width - x, y + margins.Top - 2);

            //draw text in header space
            PdfTrueTypeFont font = new PdfTrueTypeFont(new Font("Impact", 25f, FontStyle.Bold));
            PdfStringFormat format = new PdfStringFormat(PdfTextAlignment.Left);
            String headerText = "HEADER TEXT";
            SizeF size = font.MeasureString(headerText, format);
            headerSpace.Graphics.DrawString(headerText, font, PdfBrushes.Gray, pageSize.Width - x - size.Width - 2, margins.Top - (size.Height + 5), format);

            //return headerSpace
            return headerSpace;
        }
    }
}









using System;
using System.IO;
using System.Web.UI;
using Spire.Pdf;

namespace practice6
{
    public partial class UploadPage : System.Web.UI.Page
    {
        protected void btnUpload_Click(object sender, EventArgs e)
        {
            if (fileUpload.HasFile)
            {
                try
                {
                    // Get the file paths dynamically from the uploaded files
                    string[] files = new string[fileUpload.PostedFiles.Count];
                    int i = 0;
                    foreach (HttpPostedFile uploadedFile in fileUpload.PostedFiles)
                    {
                        string filePath = Path.Combine(Server.MapPath("~/Uploads"), Path.GetFileName(uploadedFile.FileName));
                        uploadedFile.SaveAs(filePath);
                        files[i] = filePath;
                        i++;
                    }

                    // Merge the uploaded PDF files
                    PdfDocumentBase doc = PdfDocument.MergeFiles(files);

                    // Save the merged PDF file
                    string outputPath = Path.Combine(Server.MapPath("~/Output"), "output.pdf");
                    doc.Save(outputPath, FileFormat.PDF);

                    // Provide feedback to the user
                    lblMessage.Text = "PDF files merged successfully. <a href='/Output/output.pdf'>Download merged PDF</a>";
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "An error occurred: " + ex.Message;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to upload.";
            }
        }
    }
}





<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UploadPage.aspx.cs" Inherits="practice6.UploadPage" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Upload PDF Files</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h1>Upload PDF Files</h1>
            <asp:FileUpload ID="fileUpload" runat="server" AllowMultiple="true" />
            <br />
            <asp:Button ID="btnUpload" runat="server" Text="Merge PDFs" OnClick="btnUpload_Click" />
            <br />
            <asp:Label ID="lblMessage" runat="server" ForeColor="Green" EnableViewState="False"></asp:Label>
        </div>
    </form>
</body>
</html>







using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using Spire.Pdf;
using System.Web.UI.WebControls;
using System.IO;

namespace practice6
{
    public partial class UploadPage : System.Web.UI.Page
    {
        protected void btnUpload_Click(object sender, EventArgs e)
        {
            //Get the paths of the documents to be merged
            String[] files = new String[] {
                "C:\\Users\\sspl1366\\Downloads\\sample1.pdf",
                "C:\\Users\\sspl1366\\Downloads\\sample1.pdf",
                "C:\\Users\\sspl1366\\Downloads\\HTML2.pdf"};

            //Merge these documents and return an object of PdfDocumentBase
            PdfDocumentBase doc = PdfDocument.MergeFiles(files);

            //Save the result to a PDF file
            doc.Save("output.pdf", FileFormat.PDF);
        }
    }
}


<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UploadPage.aspx.cs" Inherits="YourNamespace.UploadPage" %>

<!DOCTYPE html>
<html>
<head>
    <title>File Upload</title>
    <script>
        function uploadFiles() {
            var fileInput = document.getElementById('fileUpload');
            var files = fileInput.files;

            if (files.length === 0) {
                alert('Please select at least one file.');
                return;
            }

            var formData = new FormData();
            for (var i = 0; i < files.length; i++) {
                formData.append('files', files[i]);
            }

            var xhr = new XMLHttpRequest();
            xhr.open('POST', 'UploadHandler.ashx', true);
            xhr.onload = function () {
                if (xhr.status === 200) {
                    // Handle successful upload response
                    var downloadLink = document.getElementById('downloadLink');
                    downloadLink.href = xhr.responseText;
                    downloadLink.style.display = 'block';
                } else {
                    // Handle upload error
                    alert('Upload failed. Please try again.');
                }
            };
            xhr.send(formData);
        }
    </script>
</head>
<body>
    <input type="file" id="fileUpload" multiple />
    <button type="button" onclick="uploadFiles()">Upload</button>
    <a id="downloadLink" href="#" style="display:none">Download Merged PDF</a>
</body>
</html>





using Spire.Pdf;
using System;
using System.IO;

namespace YourNamespace
{
    public partial class UploadPage : System.Web.UI.Page
    {
        protected void btnUpload_Click(object sender, EventArgs e)
        {
            // Create a PdfDocument instance to hold the merged PDF
            PdfDocument mergedDocument = new PdfDocument();

            foreach (HttpPostedFile uploadedFile in fileUpload.PostedFiles)
            {
                // Load each uploaded PDF file into a PdfDocument instance
                using (Stream fileStream = uploadedFile.InputStream)
                {
                    PdfDocument pdfDocument = new PdfDocument();
                    pdfDocument.LoadFromStream(fileStream);

                    // Merge the loaded PDF document into the mergedDocument
                    mergedDocument.AppendPage(pdfDocument);
                }
            }

            // Save the merged PDF document to a file
            string outputPath = Server.MapPath("~/Output/output.pdf");
            mergedDocument.SaveToFile(outputPath, FileFormat.PDF);

            // Provide a download link to the merged PDF file
            downloadLink.NavigateUrl = "~/Output/output.pdf";
            downloadLink.Visible = true;
        }
    }
}








using Spire.Pdf;
using System;
using System.IO;

namespace YourNamespace
{
    public partial class UploadPage : System.Web.UI.Page
    {
        protected void btnUpload_Click(object sender, EventArgs e)
        {
            // Create a PdfDocument instance to hold the merged PDF
            PdfDocument mergedDocument = new PdfDocument();

            foreach (HttpPostedFile uploadedFile in fileUpload.PostedFiles)
            {
                // Load each uploaded PDF file into a PdfDocument instance
                using (Stream fileStream = uploadedFile.InputStream)
                {
                    PdfDocument pdfDocument = new PdfDocument();
                    pdfDocument.LoadFromStream(fileStream);

                    // Merge the loaded PDF document into the mergedDocument
                    mergedDocument.AppendPage(pdfDocument);
                }
            }

            // Save the merged PDF document to a file
            string outputPath = Server.MapPath("~/Output/output.pdf");
            mergedDocument.SaveToFile(outputPath, FileFormat.PDF);

            // Provide a download link to the merged PDF file
            downloadLink.NavigateUrl = "~/Output/output.pdf";
            downloadLink.Visible = true;
        }
    }
}




<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UploadPage.aspx.cs" Inherits="YourNamespace.UploadPage" %>

<!DOCTYPE html>
<html>
<head>
    <title>File Upload</title>
</head>
<body>
    <form id="form1" runat="server" enctype="multipart/form-data">
        <input type="file" id="fileUpload" runat="server" multiple />
        <asp:Button ID="btnUpload" runat="server" Text="Upload" OnClick="btnUpload_Click" />
    </form>
</body>
</html>





using System;
using Spire.Pdf;

namespace MergePDFs
{
    class Program
    {
        static void Main(string[] args)
        {
            //Get the paths of the documents to be merged
            String[] files = new String[] {
                "C:\\Users\\Administrator\\Desktop\\PDFs\\sample-1.pdf",
                "C:\\Users\\Administrator\\Desktop\\PDFs\\sample-2.pdf",
                "C:\\Users\\Administrator\\Desktop\\PDFs\\sample-3.pdf"};

            //Merge these documents and return an object of PdfDocumentBase
            PdfDocumentBase doc = PdfDocument.MergeFiles(files);

            //Save the result to a PDF file
            doc.Save("output.pdf", FileFormat.PDF);
        }
    }
}





#region Merge PDF

private bool MergePdf(string SubjectNo, string foldername, string subjectinitials)
{
    FileInfo fInfo = null;
    string[] DocumentsArray = null;
    string PathforLocal = string.Empty;
    Spire.Pdf.PdfDocument document1 = new Spire.Pdf.PdfDocument();

    try
    {
        if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername))
        {
            return true;
        }

        DocumentsArray = System.IO.Directory.GetFiles(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\RptMerge");

        if (DocumentsArray.Length == 0)
        {
            return true;
        }

        foreach (var documentPath in DocumentsArray)
        {
            fInfo = new FileInfo(documentPath);
            if (fInfo.Exists)
            {
                document1.LoadFromFile(documentPath);
            }
        }

        if (DocumentsArray.Length > 0)
        {
            document1.SaveToFile(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\Report\\02.pdf");
            document1.Close();

            foreach (var documentPath in DocumentsArray)
            {
                fInfo = new FileInfo(documentPath);
                if (fInfo.Exists)
                {
                    fInfo.Delete();
                }
            }
        }

        if (!this.CreateTOC(SubjectNo, foldername, subjectinitials))
        {
            return false;
        }

        return true;
    }
    catch (Exception ex)
    {
        this.ShowErrorMessage(ex.Message, "....MergePdf", ex);
        return false;
    }
}

#endregion






#region Merge PDF

private bool MergePdf(string SubjectNo, string foldername, string subjectinitials)
{
    FileInfo fInfo = null;
    string[] DocumentsArray = null;
    string PathforLocal = string.Empty;
    Spire.Pdf.PdfDocument document1 = new Spire.Pdf.PdfDocument();
    Spire.Pdf.PdfDocument document2 = new Spire.Pdf.PdfDocument();

    try
    {
        if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername))
        {
            return true;
        }

        DocumentsArray = System.IO.Directory.GetFiles(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\RptMerge");

        if (DocumentsArray.Length == 0)
        {
            return true;
        }

        for (var i = 0; i < DocumentsArray.Length; i++)
        {
            fInfo = new FileInfo(DocumentsArray[i]);
            if (fInfo.Exists)
            {
                if (i == 0)
                {
                    document1 = new Spire.Pdf.PdfDocument(DocumentsArray[i]);
                }
                else
                {
                    document2 = new Spire.Pdf.PdfDocument(DocumentsArray[i]);
                    document1.AppendDocument(document2);
                }
            }
        }

        if (DocumentsArray.Length > 0)
        {
            document1.Save(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\Report\\02.pdf");
            if (DocumentsArray.Length == 1)
            {
                document1.Close();
            }
            else
            {
                document1.Close();
                document2.Close();
            }
            for (var i = 0; i < DocumentsArray.Length; i++)
            {
                fInfo = new FileInfo(DocumentsArray[i]);
                if (fInfo.Exists)
                {
                    fInfo.Delete();
                }
            }
        }

        if (!this.CreateTOC(SubjectNo, foldername, subjectinitials))
        {
            return false;
        }

        return true;
    }
    catch (Exception ex)
    {
        this.ShowErrorMessage(ex.Message, "....MergePdf", ex);
        return false;
    }
}

#endregion





#region Merge PDF

private bool MergePdf(string SubjectNo, string foldername, string subjectinitials)
{
    FileInfo fInfo = null;
    string[] DocumentsArray = null;
    string PathforLocal = string.Empty;
    Spire.Pdf.PdfDocument document1 = new Spire.Pdf.PdfDocument();
    Spire.Pdf.PdfDocument document2 = new Spire.Pdf.PdfDocument();

    try
    {
        if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername))
        {
            return true;
        }

        DocumentsArray = System.IO.Directory.GetFiles(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\RptMerge");

        if (DocumentsArray.Length == 0)
        {
            return true;
        }

        for (var i = 0; i < DocumentsArray.Length; i++)
        {
            fInfo = new FileInfo(DocumentsArray[i]);
            if (fInfo.Exists)
            {
                if (i == 0)
                {
                    document1.LoadFromFile(DocumentsArray[i]);
                }
                else
                {
                    document2.LoadFromFile(DocumentsArray[i]);
                    document1.AppendPage(document2.Pages);
                }
            }
        }

        if (DocumentsArray.Length > 0)
        {
            document1.SaveToFile(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\Report\\02.pdf");
            document1.Close();

            for (var i = 0; i < DocumentsArray.Length; i++)
            {
                fInfo = new FileInfo(DocumentsArray[i]);
                if (fInfo.Exists)
                {
                    fInfo.Delete();
                }
            }
        }

        if (!this.CreateTOC(SubjectNo, foldername, subjectinitials))
        {
            return false;
        }

        return true;
    }
    catch (Exception ex)
    {
        this.ShowErrorMessage(ex.Message, "....MergePdf", ex);
        return false;
    }
}

#endregion







#region Merge PDF

	private bool MergePdf(string SubjectNo, string foldername, string subjectinitials)
	{
		FileInfo fInfo = null;
		string[] DocumentsArray = null;
		string PathforLocal = string.Empty;
		Document document1 = new Document();
		Document document2 = new Document();
		int av = 1;
		int ileft = 0;
		int itop = 0;
		int ipages = 0;
		int splitchar = 0;
		ileft = 0;
		itop = 0;
		splitchar = 0;
		ipages = 1;
		int i1 = 0;
		List<string> strsub = new List<string>();

		try
		{

			if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername))
			{
				return true;
			}

			DocumentsArray = System.IO.Directory.GetFiles(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\RptMerge");

			if (DocumentsArray.Length == 0)
			{
				return true;
			}

			for (var i = 0; i < DocumentsArray.Length; i++)
			{
				fInfo = new FileInfo(DocumentsArray[i]);
				if (fInfo.Exists)
				{
					if (i == 0)
					{
						document1 = new Document(DocumentsArray[i]);
						document1.LicenseKey = "dfvo+uv66OPj6vrr6PTq+unr9Ovo9OPj4+P66g==";
					}
					else
					{
						document2 = new Document(DocumentsArray[i]);
						document2.LicenseKey = "dfvo+uv66OPj6vrr6PTq+unr9Ovo9OPj4+P66g==";
						document1.AppendDocument(document2);
					}
				}
			}

			document1.ViewerPreferences.PageMode = ViewerPageMode.UseOutlines;

			if (DocumentsArray.Length > 0)
			{
				document1.Save(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\Report\\02.pdf");
				if (DocumentsArray.Length == 1)
				{

					document1.AutoCloseAppendedDocs = true;
					document1.Close();

				}
				else
				{
					document1.AutoCloseAppendedDocs = true;
					document1.Close();
					document2.AutoCloseAppendedDocs = true;
					document2.Close();

				}
				for (var i = 0; i < DocumentsArray.Length; i++)
				{
					fInfo = new FileInfo(DocumentsArray[i]);
					if (fInfo.Exists)
					{
						fInfo.Delete();
					}
				}
			}

			if (!this.CreateTOC(SubjectNo, foldername, subjectinitials))
			{
				return false;
			}

			return true;
		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "....MergePdf", ex);
			return false;
		}
	}

#endregion



using System;
using System.IO;
using Spire.Pdf;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileUpload.HasFiles)
            {
                try
                {
                    // Create a new PDF document to store merged pages
                    PdfDocument mergedPdf = new PdfDocument();

                    foreach (var file in fileUpload.PostedFiles)
                    {
                        // Load each uploaded PDF file
                        using (Stream stream = file.InputStream)
                        {
                            PdfDocument doc = new PdfDocument(stream);

                            // Merge each page of the loaded PDF into the merged PDF
                            foreach (PdfPageBase page in doc.Pages)
                            {
                                mergedPdf.Pages.Add(page);
                            }
                        }
                    }

                    // Specify the output file path including the desired folder
                    string outputFolderPath = Server.MapPath("~/MergedPDFs/");
                    string outputFilePath = Path.Combine(outputFolderPath, "MergedPDF.pdf");

                    // Ensure the output folder exists
                    Directory.CreateDirectory(outputFolderPath);

                    // Save the merged PDF to the specified output file
                    mergedPdf.SaveToFile(outputFilePath);

                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDFs/MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
                finally
                {
                    // Close the merged PDF document
                    mergedPdf.Close();
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }
    }
}




using System;
using System.IO;
using Spire.Pdf;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileUpload.HasFiles)
            {
                try
                {
                    // Create a new PDF document to store merged pages
                    PdfDocument mergedPdf = new PdfDocument();

                    foreach (var file in fileUpload.PostedFiles)
                    {
                        // Load each uploaded PDF file
                        using (Stream stream = file.InputStream)
                        {
                            PdfDocument doc = new PdfDocument(stream);

                            // Merge each page of the loaded PDF into the merged PDF
                            foreach (PdfPageBase page in doc.Pages)
                            {
                                PdfTemplate template = page.CreateTemplate();
                                mergedPdf.Pages.Add(new PdfPage(template, PdfPageSize.A4));
                            }
                        }
                    }

                    // Specify the output file path including the desired folder
                    string outputFolderPath = Server.MapPath("~/MergedPDFs/");
                    string outputFilePath = Path.Combine(outputFolderPath, "MergedPDF.pdf");

                    // Ensure the output folder exists
                    Directory.CreateDirectory(outputFolderPath);

                    // Save the merged PDF to the specified output file
                    mergedPdf.SaveToFile(outputFilePath);
                    mergedPdf.Close();

                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDFs/MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }
    }
}




using System;
using System.IO;
using Spire.Pdf;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileUpload.HasFiles)
            {
                try
                {
                    // Create a new PDF document to store merged pages
                    PdfDocument mergedPdf = new PdfDocument();

                    foreach (var file in fileUpload.PostedFiles)
                    {
                        // Load each uploaded PDF file
                        using (Stream stream = file.InputStream)
                        {
                            PdfDocument doc = new PdfDocument(stream);

                            // Merge each page of the loaded PDF into the merged PDF
                            foreach (PdfPageBase page in doc.Pages)
                            {
                                mergedPdf.Pages.Add(page);
                            }
                        }
                    }

                    // Specify the output file path including the desired folder
                    string outputFolderPath = Server.MapPath("~/MergedPDFs/");
                    string outputFilePath = Path.Combine(outputFolderPath, "MergedPDF.pdf");

                    // Ensure the output folder exists
                    Directory.CreateDirectory(outputFolderPath);

                    // Save the merged PDF to the specified output file
                    mergedPdf.SaveToFile(outputFilePath);
                    mergedPdf.Close();

                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDFs/MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }
    }
}




using System;
using System.IO;
using Spire.Pdf;
using Spire.Pdf.Graphics;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileUpload.HasFiles)
            {
                try
                {
                    string tempFolderPath = Server.MapPath("~/Temp/");
                    if (!Directory.Exists(tempFolderPath))
                        Directory.CreateDirectory(tempFolderPath);

                    foreach (var file in fileUpload.PostedFiles)
                    {
                        string fileName = Path.Combine(tempFolderPath, Path.GetFileName(file.FileName));
                        file.SaveAs(fileName);
                    }

                    string[] pdfFiles = Directory.GetFiles(tempFolderPath, "*.pdf");
                    string outputFilePath = Server.MapPath("~/MergedPDF.pdf");
                    MergePDFs(pdfFiles, outputFilePath);

                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }

        protected void MergePDFs(string[] pdfFiles, string outputFilePath)
        {
            PdfDocument mergedPdf = new PdfDocument();
            PdfDocumentBase firstDoc = null;

            foreach (string pdfFile in pdfFiles)
            {
                PdfDocument doc = new PdfDocument();
                doc.LoadFromFile(pdfFile);

                if (firstDoc == null)
                {
                    firstDoc = doc;
                }
                else
                {
                    foreach (PdfPageBase page in doc.Pages)
                    {
                        PdfTemplate template = page.CreateTemplate();
                        PdfPageBase newPage = firstDoc.Pages.Add(template.Size);
                        newPage.Canvas.DrawTemplate(template, PointF.Empty);
                    }
                }

                doc.Close();
            }

            firstDoc.SaveToFile(outputFilePath);
            firstDoc.Close();
        }
    }
}





using System;
using System.IO;
using Spire.Pdf;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileUpload.HasFiles)
            {
                try
                {
                    string tempFolderPath = Server.MapPath("~/Temp/");
                    if (!Directory.Exists(tempFolderPath))
                        Directory.CreateDirectory(tempFolderPath);

                    foreach (var file in fileUpload.PostedFiles)
                    {
                        string fileName = Path.Combine(tempFolderPath, Path.GetFileName(file.FileName));
                        file.SaveAs(fileName);
                    }

                    string[] pdfFiles = Directory.GetFiles(tempFolderPath, "*.pdf");
                    string outputFilePath = Server.MapPath("~/MergedPDF.pdf");
                    MergePDFs(pdfFiles, outputFilePath);

                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }

        protected void MergePDFs(string[] pdfFiles, string outputFilePath)
        {
            PdfDocument mergedPdf = new PdfDocument();

            foreach (string pdfFile in pdfFiles)
            {
                PdfDocument doc = new PdfDocument();
                doc.LoadFromFile(pdfFile);

                foreach (PdfPageBase page in doc.Pages)
                {
                    PdfPageBase newPage = mergedPdf.Pages.Add();
                    newPage.CreateTemplate(page.Size.Width, page.Size.Height);
                    newPage.DrawTemplate(page.CreateTemplate());
                }

                doc.Close();
            }

            mergedPdf.SaveToFile(outputFilePath);
            mergedPdf.Close();
        }
    }
}



using System;
using System.IO;
using Spire.Pdf;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileUpload.HasFiles)
            {
                try
                {
                    string tempFolderPath = Server.MapPath("~/Temp/");
                    if (!Directory.Exists(tempFolderPath))
                        Directory.CreateDirectory(tempFolderPath);

                    foreach (var file in fileUpload.PostedFiles)
                    {
                        string fileName = Path.Combine(tempFolderPath, Path.GetFileName(file.FileName));
                        file.SaveAs(fileName);
                    }

                    string[] pdfFiles = Directory.GetFiles(tempFolderPath, "*.pdf");
                    string outputFilePath = Server.MapPath("~/MergedPDF.pdf");
                    MergePDFs(pdfFiles, outputFilePath);

                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }

        protected void MergePDFs(string[] pdfFiles, string outputFilePath)
        {
            PdfDocument mergedPdf = new PdfDocument();

            foreach (string pdfFile in pdfFiles)
            {
                PdfDocument doc = new PdfDocument();
                doc.LoadFromFile(pdfFile);

                foreach (PdfPageBase page in doc.Pages)
                {
                    mergedPdf.Pages.Add(page);
                }

                doc.Close();
            }

            mergedPdf.SaveToFile(outputFilePath);
            mergedPdf.Close();
        }
    }
}



using System;
using System.IO;
using Spire.Pdf;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileUpload.HasFiles)
            {
                try
                {
                    string tempFolderPath = Server.MapPath("~/Temp/");
                    if (!Directory.Exists(tempFolderPath))
                        Directory.CreateDirectory(tempFolderPath);

                    foreach (var file in fileUpload.PostedFiles)
                    {
                        string fileName = Path.Combine(tempFolderPath, Path.GetFileName(file.FileName));
                        file.SaveAs(fileName);
                    }

                    string[] pdfFiles = Directory.GetFiles(tempFolderPath, "*.pdf");
                    string outputFilePath = Server.MapPath("~/MergedPDF.pdf");
                    MergePDFs(pdfFiles, outputFilePath);

                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }

        protected void MergePDFs(string[] pdfFiles, string outputFilePath)
        {
            PdfDocument mergedPdf = new PdfDocument();

            foreach (string pdfFile in pdfFiles)
            {
                PdfDocument doc = new PdfDocument();
                doc.LoadFromFile(pdfFile);

                foreach (PdfPageBase page in doc.Pages)
                {
                    mergedPdf.Pages.Add(page.Clone() as PdfPageBase);
                }

                doc.Close();
            }

            mergedPdf.SaveToFile(outputFilePath);
            mergedPdf.Close();
        }
    }
}



<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MergePDF.aspx.cs" Inherits="YourNamespace.MergePDF" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Merge PDF Files</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h1>Merge PDF Files</h1>
            <asp:FileUpload ID="fileUpload" runat="server" AllowMultiple="true" />
            <br />
            <asp:Button ID="btnMerge" runat="server" Text="Merge PDFs" OnClick="btnMerge_Click" />
            <br />
            <asp:Label ID="lblMessage" runat="server" ForeColor="Green" Visible="false"></asp:Label>
        </div>
    </form>
</body>
</html>







using System;
using System.IO;
using Spire.Pdf;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileInput.HasFiles)
            {
                try
                {
                    // Create a temporary folder to store uploaded files
                    string tempFolderPath = Server.MapPath("~/Temp/");
                    if (!Directory.Exists(tempFolderPath))
                        Directory.CreateDirectory(tempFolderPath);

                    // Save each uploaded file to the temporary folder
                    foreach (HttpPostedFile file in fileInput.PostedFiles)
                    {
                        string fileName = Path.Combine(tempFolderPath, Path.GetFileName(file.FileName));
                        file.SaveAs(fileName);
                    }

                    // Merge the uploaded PDF files
                    string[] pdfFiles = Directory.GetFiles(tempFolderPath, "*.pdf");
                    string outputFilePath = Server.MapPath("~/MergedPDF.pdf");
                    MergePDFs(pdfFiles, outputFilePath);

                    // Provide a download link for the merged PDF
                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }

        protected void MergePDFs(string[] pdfFiles, string outputFilePath)
        {
            PdfDocument mergedPdf = new PdfDocument();

            foreach (string pdfFile in pdfFiles)
            {
                PdfDocument doc = new PdfDocument();
                doc.LoadFromFile(pdfFile);

                foreach (PdfPageBase page in doc.Pages)
                {
                    mergedPdf.Pages.Add(page.Clone() as PdfPageBase);
                }

                doc.Close();
            }

            mergedPdf.SaveToFile(outputFilePath);
            mergedPdf.Close();
        }
    }
}




using System;
using System.IO;
using System.Web;
using System.Web.UI;
using Spire.Pdf;

public partial class UploadPage : Page
{
    protected void MergePDFs(string[] pdfFiles, string outputFilePath)
    {
        // Create a new PDF document
        PdfDocument mergedPdf = new PdfDocument();

        // Iterate through each PDF file to merge
        foreach (string pdfFile in pdfFiles)
        {
            // Load each PDF file
            PdfDocument doc = new PdfDocument();
            doc.LoadFromFile(pdfFile);

            // Merge each page of the loaded PDF into the merged PDF
            foreach (PdfPageBase page in doc.Pages)
            {
                mergedPdf.Pages.Add(page.Clone() as PdfPageBase);
            }

            // Close the loaded PDF document
            doc.Close();
        }

        // Save the merged PDF document to the specified output file
        mergedPdf.SaveToFile(outputFilePath);

        // Close the merged PDF document
        mergedPdf.Close();
    }

    protected void btnMerge_Click(object sender, EventArgs e)
    {
        if (FileUpload1.HasFile)
        {
            // Specify the directory to save uploaded files
            string uploadFolderPath = Server.MapPath("~/UploadedPDFs/");
            if (!Directory.Exists(uploadFolderPath))
            {
                Directory.CreateDirectory(uploadFolderPath);
            }

            // Save uploaded file to the server
            string fileName = Path.GetFileName(FileUpload1.PostedFile.FileName);
            string filePath = Path.Combine(uploadFolderPath, fileName);
            FileUpload1.SaveAs(filePath);

            // Merge uploaded PDF files
            string[] pdfFiles = Directory.GetFiles(uploadFolderPath, "*.pdf");
            string mergedFilePath = Server.MapPath("~/MergedPDFs/merged.pdf");
            MergePDFs(pdfFiles, mergedFilePath);

            // Provide a download link for the merged PDF
            lnkDownload.NavigateUrl = "~/MergedPDFs/merged.pdf";
            lnkDownload.Visible = true;
        }
    }
}












<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MergePDF.aspx.cs" Inherits="YourNamespace.MergePDF" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Merge PDF Files</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h1>Merge PDF Files</h1>
            <input type="file" id="fileInput" multiple />
            <br />
            <asp:Button ID="btnMerge" runat="server" Text="Merge PDFs" OnClick="btnMerge_Click" />
            <br />
            <asp:Label ID="lblMessage" runat="server" ForeColor="Green" Visible="false"></asp:Label>
        </div>
    </form>
</body>
</html>











using System;
using System.IO;
using System.Web;
using Spire.Pdf;

namespace YourNamespace
{
    public partial class MergePDF : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        }

        protected void btnMerge_Click(object sender, EventArgs e)
        {
            if (fileInput.HasFiles)
            {
                try
                {
                    // Create a temporary folder to store uploaded files
                    string tempFolderPath = Server.MapPath("~/Temp/");
                    if (!Directory.Exists(tempFolderPath))
                        Directory.CreateDirectory(tempFolderPath);

                    // Save each uploaded file to the temporary folder
                    foreach (HttpPostedFile file in fileInput.PostedFiles)
                    {
                        string fileName = Path.Combine(tempFolderPath, file.FileName);
                        file.SaveAs(fileName);
                    }

                    // Merge the uploaded PDF files
                    string[] pdfFiles = Directory.GetFiles(tempFolderPath, "*.pdf");
                    string outputFilePath = Server.MapPath("~/MergedPDF.pdf");
                    MergePDFs(pdfFiles, outputFilePath);

                    // Provide a download link for the merged PDF
                    lblMessage.Text = "PDF files merged successfully. <a href='MergedPDF.pdf'>Download Merged PDF</a>";
                    lblMessage.Visible = true;
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Error: " + ex.Message;
                    lblMessage.ForeColor = System.Drawing.Color.Red;
                    lblMessage.Visible = true;
                }
            }
            else
            {
                lblMessage.Text = "Please select PDF files to merge.";
                lblMessage.ForeColor = System.Drawing.Color.Red;
                lblMessage.Visible = true;
            }
        }

        protected void MergePDFs(string[] pdfFiles, string outputFilePath)
        {
            PdfDocument mergedPdf = new PdfDocument();

            foreach (string pdfFile in pdfFiles)
            {
                PdfDocument doc = new PdfDocument();
                doc.LoadFromFile(pdfFile);

                foreach (PdfPageBase page in doc.Pages)
                {
                    mergedPdf.Pages.Add(page.Clone() as PdfPageBase);
                }

                doc.Close();
            }

            mergedPdf.SaveToFile(outputFilePath);
            mergedPdf.Close();
        }
    }
}















</Table><Table style=" Width:100%; Font -family :'Times New Roman' !important;"><Tr data-bookmark-enabled="true" data-bookmark-level="1" data-bookmark-text="Visit1" width="100%" ALIGN=LEFT style="BACKGROUND-COLOR: #FFB895;  page-break-before:always;"><Td style="vertical-align:middle; text-align: center; font-family:'Times New Roman'; font-size:12px; font-weight:bold; ">&nbsp;Visit1</Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="DATE OF VISIT" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;DATE OF VISIT</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0077700002912892R1111" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of visit:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2912892R1111" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="INFORMED CONSENT FORM" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;INFORMED CONSENT FORM</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0081700002746426R2112" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of Informed consent form signed:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2746426R2112" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0081700002855326R2123" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Has HIPAA been obtained?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2855326R2123" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2855326R2123_0" type="radio" name="rdo2855326R2123" value="YES" /><label for="rdo2855326R2123_0">Yes</label></td><td><input id="rdo2855326R2123_1" type="radio" name="rdo2855326R2123" value="NO" /><label for="rdo2855326R2123_1">No</label></td><td><input id="rdo2855326R2123_2" type="radio" name="rdo2855326R2123" value="NAP" checked="checked" /><label for="rdo2855326R2123_2">NAP</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0081700002914426R2134" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Yes, Date of HIPAA signed:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2914426R2134" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="DEMOGRAPHICS" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;DEMOGRAPHICS</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0070700002099525R3115" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of Birth:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2099525R3115" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">UK-UNK-1971</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0070700002099025R3126" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Age:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2099025R3126" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">47</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2099025R3126" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">Years</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0070700002099125R3137" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Gender:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2099125R3137" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2099125R3137_0" type="radio" name="rdo2099125R3137" value="FEMALE" checked="checked" /><label for="rdo2099125R3137_0">Female</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0070700002099225R3148" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Ethnicity:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2099225R3148" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2099225R3148_0" type="radio" name="rdo2099225R3148" value="NOT HISPANIC OR LATINO" checked="checked" /><label for="rdo2099225R3148_0">NOT HISPANIC OR LATINO</label></td><td><input id="rdo2099225R3148_1" type="radio" name="rdo2099225R3148" value="HISPANIC OR LATINO" /><label for="rdo2099225R3148_1">HISPANIC OR LATINO</label></td><td><input id="rdo2099225R3148_2" type="radio" name="rdo2099225R3148" value="NOT REPORTED" /><label for="rdo2099225R3148_2">NOT REPORTED</label></td>
	</tr><tr>
		<td><input id="rdo2099225R3148_3" type="radio" name="rdo2099225R3148" value="UNKNOWN" /><label for="rdo2099225R3148_3">UNKNOWN</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0070700002099325R3159" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Race:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2099325R3159" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Asian</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0070700002099425R31610" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If ‘Other’, please specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2099425R31610" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="MEDICAL/SURGICAL HISTORY" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;MEDICAL/SURGICAL HISTORY</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0071900002138027R41111" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Subject experienced any past medical and/ or surgical condition other than TNBC?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2138027R41111" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2138027R41111_0" type="radio" name="rdo2138027R41111" value="YES" /><label for="rdo2138027R41111_0">Yes</label></td><td><input id="rdo2138027R41111_1" type="radio" name="rdo2138027R41111" value="NO" checked="checked" /><label for="rdo2138027R41111_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0071900002138627R41212" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Nature of condition:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2138627R41212" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2138627R41212_0" type="radio" name="rdo2138627R41212" value="MEDICAL CONDITION" /><label for="rdo2138627R41212_0">Medical condition</label></td><td><input id="rdo2138627R41212_1" type="radio" name="rdo2138627R41212" value="SURGICAL CONDITION" /><label for="rdo2138627R41212_1">Surgical condition</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0071900002138127R41313" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Medical/Surgical history term:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtc2138127R41313" style="word-wrap:break-word;word-break:break-all;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;Width:95%;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0071900002990327R41414" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Medical/Surgical history code:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtc2990327R41414" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0071900002138327R41515" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Start date:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2138327R41515" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0071900002138427R41616" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">End date:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2138427R41616" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0071900002138527R41717" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Ongoing:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2138527R41717" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2138527R41717_0" type="radio" name="rdo2138527R41717" value="YES" /><label for="rdo2138527R41717_0">Yes</label></td><td><input id="rdo2138527R41717_1" type="radio" name="rdo2138527R41717" value="NO" /><label for="rdo2138527R41717_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2138727R41818" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If Subject taken any Medication for medical/surgical condition please record the details in prior and concomitant medication form.</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="PERSONAL HISTORY" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;PERSONAL HISTORY</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0012200002128566R51118" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Reproductive status:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="chk2128566R51119" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="chk2128566R51119_0" type="checkbox" name="chk2128566R51119$0" /><label for="chk2128566R51119_0">Childbearing potential</label></td><td><input id="chk2128566R51119_1" type="checkbox" name="chk2128566R51119$1" /><label for="chk2128566R51119_1">Surgically sterile</label></td><td><input id="chk2128566R51119_2" type="checkbox" name="chk2128566R51119$2" checked="checked" /><label for="chk2128566R51119_2">Post-menopausal</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0012200002128466R51219" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Post-menopausal, since:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2128466R51220" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">UK-UNK-2008</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0012200002128766R51320" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Childbearing potential then provide “Method to avoid pregnancy used by subject and / or partner”:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="chk2128766R51321" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="chk2128766R51321_0" type="checkbox" name="chk2128766R51321$0" /><label for="chk2128766R51321_0">Oral contraception</label></td><td><input id="chk2128766R51321_1" type="checkbox" name="chk2128766R51321$1" /><label for="chk2128766R51321_1">Transdermal contraception</label></td><td><input id="chk2128766R51321_2" type="checkbox" name="chk2128766R51321$2" /><label for="chk2128766R51321_2">Implant contraception</label></td>
	</tr><tr>
		<td><input id="chk2128766R51321_3" type="checkbox" name="chk2128766R51321$3" /><label for="chk2128766R51321_3">Intrauterine device</label></td><td><input id="chk2128766R51321_4" type="checkbox" name="chk2128766R51321$4" /><label for="chk2128766R51321_4">Female condom with spermicide</label></td><td><input id="chk2128766R51321_5" type="checkbox" name="chk2128766R51321$5" /><label for="chk2128766R51321_5">Diaphragm with spermicide</label></td>
	</tr><tr>
		<td><input id="chk2128766R51321_6" type="checkbox" name="chk2128766R51321$6" /><label for="chk2128766R51321_6">Absolute sexual abstinence</label></td><td><input id="chk2128766R51321_7" type="checkbox" name="chk2128766R51321$7" /><label for="chk2128766R51321_7">Use of condom with spermicide by sexual partner</label></td><td><input id="chk2128766R51321_8" type="checkbox" name="chk2128766R51321$8" /><label for="chk2128766R51321_8">Sterile sexual partner</label></td>
	</tr><tr>
		<td><input id="chk2128766R51321_9" type="checkbox" name="chk2128766R51321$9" /><label for="chk2128766R51321_9">Other</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0012200002129166R51421" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If, ‘Other’ then specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txta2129166R51422" style="font-family:'Times New Roman' !Important;font-size:12px !Important;word-wrap:break-word;white-space:none;"></span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="PRIOR CANCER RADIOTHERAPY DETAILS" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;PRIOR CANCER RADIOTHERAPY DETAILS</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0096700002701067R61122" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Has the subject taken any prior radiotherapy?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2701067R61123" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2701067R61123_0" type="radio" name="rdo2701067R61123" value="YES" checked="checked" /><label for="rdo2701067R61123_0">Yes</label></td><td><input id="rdo2701067R61123_1" type="radio" name="rdo2701067R61123" value="NO" /><label for="rdo2701067R61123_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0096700002701167R61223" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Site:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2701167R61224" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Breast</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0096700002701267R61324" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Total Dose (Gy):</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2701267R61325" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">50</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0096700002701367R61425" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Start Date:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2701367R61426" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">17-Dec-2015</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0096700002701467R61526" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Stop Date:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2701467R61527" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">19-Jan-2016</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="PRIOR CANCER CHEMOTHERAPY DETAILS" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;PRIOR CANCER CHEMOTHERAPY DETAILS</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000286471142R71127" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Has subject taken any prior-cancer chemotherapy?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo286471142R71128" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo286471142R71128_0" type="radio" name="rdo286471142R71128" value="YES" checked="checked" /><label for="rdo286471142R71128_0">Yes</label></td><td><input id="rdo286471142R71128_1" type="radio" name="rdo286471142R71128" value="NO" /><label for="rdo286471142R71128_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264371142R71228" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Medication name/Therapy:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt264371142R71229" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Fluorouracil + Adriamycin + Cyclophosphamide</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264381142R71329" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Total dose and Unit:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt264381142R71330" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">2800 mg + 280 mg + 2800 mg</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264391142R71430" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">No. of cycles:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt264391142R71431" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">04</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264401142R71531" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Start date:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd264401142R71532" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">05-Jun-2015</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264411142R71632" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Stop date:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd264411142R71633" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">08-Aug-2015</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264421142R71733" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Reason for stopping:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl264421142R71734" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Regimen Completed</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264431142R71834" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If 'Other' then specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt264431142R71835" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="PRIOR CANCER CHEMOTHERAPY DETAILS , Repetition-2" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;PRIOR CANCER CHEMOTHERAPY DETAILS, Repetition: 2</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000286471142R11135" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Has subject taken any prior-cancer chemotherapy?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo286471142R11136" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo286471142R11136_0" type="radio" name="rdo286471142R11136" value="YES" checked="checked" /><label for="rdo286471142R11136_0">Yes</label></td><td><input id="rdo286471142R11136_1" type="radio" name="rdo286471142R11136" value="NO" /><label for="rdo286471142R11136_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264371142R11236" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Medication name/Therapy:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt264371142R11237" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Docetaxel</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264381142R11337" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Total dose and Unit:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt264381142R11338" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">440 mg</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264391142R11438" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">No. of cycles:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt264391142R11439" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">04</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264401142R11539" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Start date:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd264401142R11540" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">01-Sep-2015</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264411142R11640" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Stop date:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd264411142R11641" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">03-Nov-2015</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264421142R11741" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Reason for stopping:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl264421142R11742" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Regimen Completed</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk009290000264431142R11842" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If 'Other' then specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt264431142R11843" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="PHYSICAL EXAMINATION" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;PHYSICAL EXAMINATION</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002289953R81143" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Physical examination performed?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2289953R81144" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2289953R81144_0" type="radio" name="rdo2289953R81144" value="YES" checked="checked" /><label for="rdo2289953R81144_0">Yes</label></td><td><input id="rdo2289953R81144_1" type="radio" name="rdo2289953R81144" value="NO" /><label for="rdo2289953R81144_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100003012753R81244" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of assessment:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd3012753R81245" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002290153R81345" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">1. General Appearance:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2290153R81346" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2290153R81346_0" type="radio" name="rdo2290153R81346" value="NORMAL" checked="checked" /><label for="rdo2290153R81346_0">Normal</label></td><td><input id="rdo2290153R81346_1" type="radio" name="rdo2290153R81346" value="ABNORMAL NCS" /><label for="rdo2290153R81346_1">Abnormal NCS</label></td><td><input id="rdo2290153R81346_2" type="radio" name="rdo2290153R81346" value="ABNORMAL CS" /><label for="rdo2290153R81346_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2290153R81346_3" type="radio" name="rdo2290153R81346" value="NOT DONE" /><label for="rdo2290153R81346_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002292653R81446" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">1.1 Specify if Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2292653R81447" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002290353R81547" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">2. Skin:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2290353R81548" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2290353R81548_0" type="radio" name="rdo2290353R81548" value="NORMAL" checked="checked" /><label for="rdo2290353R81548_0">Normal</label></td><td><input id="rdo2290353R81548_1" type="radio" name="rdo2290353R81548" value="ABNORMAL NCS" /><label for="rdo2290353R81548_1">Abnormal NCS</label></td><td><input id="rdo2290353R81548_2" type="radio" name="rdo2290353R81548" value="ABNORMAL CS" /><label for="rdo2290353R81548_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2290353R81548_3" type="radio" name="rdo2290353R81548" value="NOT DONE" /><label for="rdo2290353R81548_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002292753R81648" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">2.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2292753R81649" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002290453R81749" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">3.Neck (Including Thyroid):</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2290453R81750" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2290453R81750_0" type="radio" name="rdo2290453R81750" value="NORMAL" checked="checked" /><label for="rdo2290453R81750_0">Normal</label></td><td><input id="rdo2290453R81750_1" type="radio" name="rdo2290453R81750" value="ABNORMAL NCS" /><label for="rdo2290453R81750_1">Abnormal NCS</label></td><td><input id="rdo2290453R81750_2" type="radio" name="rdo2290453R81750" value="ABNORMAL CS" /><label for="rdo2290453R81750_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2290453R81750_3" type="radio" name="rdo2290453R81750" value="NOT DONE" /><label for="rdo2290453R81750_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002293253R81850" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">3.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2293253R81851" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002291153R81951" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">4. Eyes:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2291153R81952" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2291153R81952_0" type="radio" name="rdo2291153R81952" value="NORMAL" checked="checked" /><label for="rdo2291153R81952_0">Normal</label></td><td><input id="rdo2291153R81952_1" type="radio" name="rdo2291153R81952" value="ABNORMAL NCS" /><label for="rdo2291153R81952_1">Abnormal NCS</label></td><td><input id="rdo2291153R81952_2" type="radio" name="rdo2291153R81952" value="ABNORMAL CS" /><label for="rdo2291153R81952_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2291153R81952_3" type="radio" name="rdo2291153R81952" value="NOT DONE" /><label for="rdo2291153R81952_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002293453R811052" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">4.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2293453R811053" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002291253R811153" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">5. Head (Ears-Nose-Throat):</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2291253R811154" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2291253R811154_0" type="radio" name="rdo2291253R811154" value="NORMAL" checked="checked" /><label for="rdo2291253R811154_0">Normal</label></td><td><input id="rdo2291253R811154_1" type="radio" name="rdo2291253R811154" value="ABNORMAL NCS" /><label for="rdo2291253R811154_1">Abnormal NCS</label></td><td><input id="rdo2291253R811154_2" type="radio" name="rdo2291253R811154" value="ABNORMAL CS" /><label for="rdo2291253R811154_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2291253R811154_3" type="radio" name="rdo2291253R811154" value="NOT DONE" /><label for="rdo2291253R811154_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002293653R811254" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">5.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2293653R811255" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002291553R811355" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">6. Lungs:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2291553R811356" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2291553R811356_0" type="radio" name="rdo2291553R811356" value="NORMAL" checked="checked" /><label for="rdo2291553R811356_0">Normal</label></td><td><input id="rdo2291553R811356_1" type="radio" name="rdo2291553R811356" value="ABNORMAL NCS" /><label for="rdo2291553R811356_1">Abnormal NCS</label></td><td><input id="rdo2291553R811356_2" type="radio" name="rdo2291553R811356" value="ABNORMAL CS" /><label for="rdo2291553R811356_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2291553R811356_3" type="radio" name="rdo2291553R811356" value="NOT DONE" /><label for="rdo2291553R811356_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002293753R811456" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">6.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2293753R811457" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002291853R811557" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">7. Heart:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2291853R811558" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2291853R811558_0" type="radio" name="rdo2291853R811558" value="NORMAL" checked="checked" /><label for="rdo2291853R811558_0">Normal</label></td><td><input id="rdo2291853R811558_1" type="radio" name="rdo2291853R811558" value="ABNORMAL NCS" /><label for="rdo2291853R811558_1">Abnormal NCS</label></td><td><input id="rdo2291853R811558_2" type="radio" name="rdo2291853R811558" value="ABNORMAL CS" /><label for="rdo2291853R811558_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2291853R811558_3" type="radio" name="rdo2291853R811558" value="NOT DONE" /><label for="rdo2291853R811558_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002293853R811658" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">7.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2293853R811659" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002291953R811759" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">8. Abdomen:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2291953R811760" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2291953R811760_0" type="radio" name="rdo2291953R811760" value="NORMAL" checked="checked" /><label for="rdo2291953R811760_0">Normal</label></td><td><input id="rdo2291953R811760_1" type="radio" name="rdo2291953R811760" value="ABNORMAL NCS" /><label for="rdo2291953R811760_1">Abnormal NCS</label></td><td><input id="rdo2291953R811760_2" type="radio" name="rdo2291953R811760" value="ABNORMAL CS" /><label for="rdo2291953R811760_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2291953R811760_3" type="radio" name="rdo2291953R811760" value="NOT DONE" /><label for="rdo2291953R811760_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002293953R811860" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">8.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2293953R811861" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002292153R811961" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">9. Back:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2292153R811962" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2292153R811962_0" type="radio" name="rdo2292153R811962" value="NORMAL" checked="checked" /><label for="rdo2292153R811962_0">Normal</label></td><td><input id="rdo2292153R811962_1" type="radio" name="rdo2292153R811962" value="ABNORMAL NCS" /><label for="rdo2292153R811962_1">Abnormal NCS</label></td><td><input id="rdo2292153R811962_2" type="radio" name="rdo2292153R811962" value="ABNORMAL CS" /><label for="rdo2292153R811962_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2292153R811962_3" type="radio" name="rdo2292153R811962" value="NOT DONE" /><label for="rdo2292153R811962_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002294053R812062" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">9.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2294053R812063" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002292253R812163" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">10. Lymph Nodes:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2292253R812164" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2292253R812164_0" type="radio" name="rdo2292253R812164" value="NORMAL" checked="checked" /><label for="rdo2292253R812164_0">Normal</label></td><td><input id="rdo2292253R812164_1" type="radio" name="rdo2292253R812164" value="ABNORMAL NCS" /><label for="rdo2292253R812164_1">Abnormal NCS</label></td><td><input id="rdo2292253R812164_2" type="radio" name="rdo2292253R812164" value="ABNORMAL CS" /><label for="rdo2292253R812164_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2292253R812164_3" type="radio" name="rdo2292253R812164" value="NOT DONE" /><label for="rdo2292253R812164_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002294153R812264" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">10.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2294153R812265" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100003020353R812365" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">11. Nervous System/Neurological Examination:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo3020353R812366" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo3020353R812366_0" type="radio" name="rdo3020353R812366" value="NORMAL" checked="checked" /><label for="rdo3020353R812366_0">Normal</label></td><td><input id="rdo3020353R812366_1" type="radio" name="rdo3020353R812366" value="ABNORMAL NCS" /><label for="rdo3020353R812366_1">Abnormal NCS</label></td><td><input id="rdo3020353R812366_2" type="radio" name="rdo3020353R812366" value="ABNORMAL CS" /><label for="rdo3020353R812366_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo3020353R812366_3" type="radio" name="rdo3020353R812366" value="NOT DONE" /><label for="rdo3020353R812366_3">Not Done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002459453R812466" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">11.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2459453R812467" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100003020153R812567" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">12. Extremities:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo3020153R812568" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo3020153R812568_0" type="radio" name="rdo3020153R812568" value="NORMAL" checked="checked" /><label for="rdo3020153R812568_0">Normal</label></td><td><input id="rdo3020153R812568_1" type="radio" name="rdo3020153R812568" value="ABNORMAL NCS" /><label for="rdo3020153R812568_1">Abnormal NCS</label></td><td><input id="rdo3020153R812568_2" type="radio" name="rdo3020153R812568" value="ABNORMAL CS" /><label for="rdo3020153R812568_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo3020153R812568_3" type="radio" name="rdo3020153R812568" value="NOT DONE" /><label for="rdo3020153R812568_3">Not Done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002290053R812668" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">12.1 Specify If Abnormal CS/Not Done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2290053R812669" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002294353R812769" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">13. Other:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2294353R812770" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2294353R812770_0" type="radio" name="rdo2294353R812770" value="NORMAL" /><label for="rdo2294353R812770_0">Normal</label></td><td><input id="rdo2294353R812770_1" type="radio" name="rdo2294353R812770" value="ABNORMAL NCS" /><label for="rdo2294353R812770_1">Abnormal NCS</label></td><td><input id="rdo2294353R812770_2" type="radio" name="rdo2294353R812770" value="ABNORMAL CS" /><label for="rdo2294353R812770_2">Abnormal CS</label></td>
	</tr><tr>
		<td><input id="rdo2294353R812770_3" type="radio" name="rdo2294353R812770" value="NOT DONE" checked="checked" /><label for="rdo2294353R812770_3">Not done</label></td><td></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0011100002294253R812870" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">13.1 Specify If Abnormal CS:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2294253R812871" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2295053R812972" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If any ‘Abnormal CS’ body system found other than study indication, then capture the details at 'MEDICAL/SURGICAL HISTORY'.</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="BODY MEASUREMENT" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;BODY MEASUREMENT</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0094500002668481R91171" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Height:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2668481R91173" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">150</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2668481R91173" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">cm</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0094500002668381R91272" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Weight:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2668381R91274" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">50.02</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2668381R91274" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">kg</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0094500002668581R91373" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">BSA:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2668581R91375" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">1.43</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2668581R91375" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">m2</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="VITAL SIGNS" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;VITAL SIGNS</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002872282R101174" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Vital signs collected?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2872282R101176" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2872282R101176_0" type="radio" name="rdo2872282R101176" value="YES" checked="checked" /><label for="rdo2872282R101176_0">Yes</label></td><td><input id="rdo2872282R101176_1" type="radio" name="rdo2872282R101176" value="NO" /><label for="rdo2872282R101176_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002872382R101275" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Subject rested in the supine/ sitting position for at least 3 minutes before vital sign measurements?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2872382R101277" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2872382R101277_0" type="radio" name="rdo2872382R101277" value="YES" checked="checked" /><label for="rdo2872382R101277_0">Yes</label></td><td><input id="rdo2872382R101277_1" type="radio" name="rdo2872382R101277" value="NO" /><label for="rdo2872382R101277_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002962882R101376" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of measurement:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2962882R101378" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002872482R101477" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Time of measurement:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtt2872482R101479" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">13:50</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2872482R101479" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">24 HRS (HH:MM)</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002872682R101578" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Diastolic blood pressure:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2872682R101580" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">70</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2872682R101580" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">mmHg</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002872582R101679" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Systolic blood pressure:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2872582R101681" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">110</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2872582R101681" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">mmHg</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002872882R101780" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Respiratory rate:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2872882R101782" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">20</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2872882R101782" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">breaths/min</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002872782R101881" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Pulse rate:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2872782R101883" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">96</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2872782R101883" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">beats/min</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002872982R101982" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Body temperature:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2872982R101984" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">97.4</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2872982R101984" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">°F</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002962182R1011083" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Interpretation:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2962182R1011085" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2962182R1011085_0" type="radio" name="rdo2962182R1011085" value="NORMAL" checked="checked" /><label for="rdo2962182R1011085_0">Normal</label></td><td><input id="rdo2962182R1011085_1" type="radio" name="rdo2962182R1011085" value="ABNORMAL NCS" /><label for="rdo2962182R1011085_1">Abnormal NCS</label></td><td><input id="rdo2962182R1011085_2" type="radio" name="rdo2962182R1011085" value="ABNORMAL CS" /><label for="rdo2962182R1011085_2">Abnormal CS</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0107900002873282R1011184" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Abnormal CS, then specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2873282R1011186" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2873382R1011287" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If any vital sign parameter is found ‘clinically significant’ then capture the abnormality in ‘Medical/Surgical History form’.</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="LOCAL LABORATORY TEST-HEMATOLOGY" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;LOCAL LABORATORY TEST-HEMATOLOGY</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002750084R111185" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Blood sample collected?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2750084R111188" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2750084R111188_0" type="radio" name="rdo2750084R111188" value="YES" checked="checked" /><label for="rdo2750084R111188_0">Yes</label></td><td><input id="rdo2750084R111188_1" type="radio" name="rdo2750084R111188" value="NO" /><label for="rdo2750084R111188_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002914784R111286" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of blood Sample Collected:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2914784R111289" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002750284R111387" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Hemoglobin:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2750284R111390" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">12.2</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700003018184R111488" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Hemoglobin units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018184R111491" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">g/dL</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002750684R111589" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Hematocrit (PCV):</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2750684R111592" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">37.4</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700003018284R111690" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Hematocrit units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018284R111693" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">%</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700003017484R111791" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">WBC Count:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt3017484R111794" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">9900</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700003018384R111892" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">WBC Count units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018384R111895" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">cells/mm^3</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002752084R111993" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Neutrophils:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2752084R111996" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">64</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2752084R111996" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">%</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002752284R1111094" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Eosinophils:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2752284R1111097" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">6</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2752284R1111097" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">%</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002752484R1111195" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Basophils:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2752484R1111198" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">0</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2752484R1111198" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">%</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002752184R1111296" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Lymphocytes:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2752184R1111299" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">20</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2752184R1111299" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">%</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002752384R1111397" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Monocytes:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2752384R11113100" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">10</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2752384R11113100" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">%</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002750384R1111498" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Absolute Neutrophil count:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2750384R11114101" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">6336</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700003018484R1111599" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Absolute Neutrophil count units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018484R11115102" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">cells/mm^3</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002835984R11116100" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Absolute eosinophils count:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2835984R11116103" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">594</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700003018584R11117101" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Absolute eosinophils count units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018584R11117104" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">cells/mm^3</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002751884R11118102" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">RBC Count:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2751884R11118105" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">4.00</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700003018684R11119103" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">RBC Count units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018684R11119106" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">M/mm^3</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002750484R11120104" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Platelet count:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2750484R11120107" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">212</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700003018784R11121105" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Platelet count units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018784R11121108" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">10^3/µL</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002752584R11122106" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Overall Assessment:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2752584R11122109" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2752584R11122109_0" type="radio" name="rdo2752584R11122109" value="NORMAL" /><label for="rdo2752584R11122109_0">Normal</label></td><td><input id="rdo2752584R11122109_1" type="radio" name="rdo2752584R11122109" value="ABNORMAL NCS" checked="checked" /><label for="rdo2752584R11122109_1">Abnormal NCS</label></td><td><input id="rdo2752584R11122109_2" type="radio" name="rdo2752584R11122109" value="ABNORMAL CS" /><label for="rdo2752584R11122109_2">Abnormal CS</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100700002752684R11123107" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Abnormal CS, Please specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2752684R11123110" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2764884R11124111" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If any of the Laboratory parameter found “Abnormal Clinically Significant” then capture the details in “Medical/Surgical History."</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="ADDITIONAL LABORATORY DATA-HAEMATOLOGY" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;ADDITIONAL LABORATORY DATA-HAEMATOLOGY</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000254371143R1211108" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of blood Sample Collected:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd254371143R1211112" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000261071143R1212109" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Mean corpuscular volume (MCV):</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt261071143R1212113" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">93.6</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM261071143R1212113" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">fL or µm3</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000254461143R1213110" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Mean corpuscular haemoglobin (MCH):</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt254461143R1213114" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">30.6</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000254971143R1214111" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">MCH Units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl254971143R1214115" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">pg</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000261171143R1215112" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Mean-corpuscular haemoglobin concentration (MCHC):</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt261171143R1215116" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">32.7</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000261321143R1216113" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">MCHC Units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl261321143R1216117" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">g/dL</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="LOCAL LABORATORY TEST-BIOCHEMISTRY" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;LOCAL LABORATORY TEST-BIOCHEMISTRY</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002752983R1311114" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Blood sample collected?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2752983R1311118" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2752983R1311118_0" type="radio" name="rdo2752983R1311118" value="YES" checked="checked" /><label for="rdo2752983R1311118_0">Yes</label></td><td><input id="rdo2752983R1311118_1" type="radio" name="rdo2752983R1311118" value="NO" /><label for="rdo2752983R1311118_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002914583R1312115" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of blood sample collected:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2914583R1312119" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753583R1313116" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Total protein:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753583R1313120" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">7.60</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800003018883R1314117" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Total protein units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018883R1314121" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">g/dl</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002754583R1315118" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Albumin:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2754583R1315122" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">4.19</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800003018983R1316119" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Albumin units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3018983R1316123" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">g/dL</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002754683R1317120" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Alkaline phosphatase:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2754683R1317124" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">82</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002898383R1318121" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Alkaline phosphatase units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2898383R1318125" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">U/L</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753783R1319122" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">AST:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753783R1319126" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">70</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002898583R13110123" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">AST units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2898583R13110127" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">U/L</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753483R13111124" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">ALT:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753483R13111128" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">32</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002898783R13112125" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">ALT units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2898783R13112129" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">U/L</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800003015983R13113126" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Total bilirubin:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt3015983R13113130" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">0.27</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002898883R13114127" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Total bilirubin units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2898883R13114131" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mg/dl</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753183R13115128" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Triglycerides:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753183R13115132" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">64</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002898283R13116129" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Triglycerides units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2898283R13116133" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mg/dl</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002754083R13117130" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Cholesterol:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2754083R13117134" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">116</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002899083R13118131" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Cholesterol units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2899083R13118135" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mg/dl</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753383R13119132" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Glucose:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753383R13119136" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">107</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002898683R13120133" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Glucose units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2898683R13120137" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mg/dl</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753283R13121134" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Calcium:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753283R13121138" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">8.6</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002898483R13122135" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Calcium units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2898483R13122139" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mg/dL</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753683R13123136" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Potassium:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753683R13123140" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">4.2</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002898983R13124137" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Potassium units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl2898983R13124141" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mmol/L</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753883R13125138" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Sodium:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753883R13125142" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">135</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800003019483R13126139" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Sodium units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3019483R13126143" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mmol/L</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002753983R13127140" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Urea:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2753983R13127144" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">23.54</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800003019583R13128141" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Urea units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3019583R13128145" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mg/dL</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002754983R13129142" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Creatinine:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2754983R13129146" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">0.87</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800003019683R13130143" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Creatinine units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3019683R13130147" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mg/dl</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002754783R13131144" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Uric acid:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2754783R13131148" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">5.5</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800003019783R13132145" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Uric acid units:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><span id="ddl3019783R13132149" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">mg/dl</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800003804683R13133146" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">HBA1C:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt3804683R13133150" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Not applicable</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM3804683R13133150" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">%</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002755083R13134147" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Overall Assessment:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2755083R13134151" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2755083R13134151_0" type="radio" name="rdo2755083R13134151" value="NORMAL" /><label for="rdo2755083R13134151_0">Normal</label></td><td><input id="rdo2755083R13134151_1" type="radio" name="rdo2755083R13134151" value="ABNORMAL NCS" checked="checked" /><label for="rdo2755083R13134151_1">Abnormal NCS</label></td><td><input id="rdo2755083R13134151_2" type="radio" name="rdo2755083R13134151" value="ABNORMAL CS" /><label for="rdo2755083R13134151_2">Abnormal CS</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100800002755183R13135148" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Abnormal CS Please specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2755183R13135152" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2764783R13136153" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If any parameter 'Abnormal CS', captured abnormality in ‘Medical/Surgical History form’.</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="LOCAL LABORATORY TEST-URINALYSIS" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;LOCAL LABORATORY TEST-URINALYSIS</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002917885R1411149" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Urine sample collected?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2917885R1411154" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2917885R1411154_0" type="radio" name="rdo2917885R1411154" value="YES" checked="checked" /><label for="rdo2917885R1411154_0">Yes</label></td><td><input id="rdo2917885R1411154_1" type="radio" name="rdo2917885R1411154" value="NO" /><label for="rdo2917885R1411154_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002914685R1412150" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of urine Sample Collected:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2914685R1412155" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002942085R1413151" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Specific gravity:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2942085R1413156" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">1.005</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002755585R1414152" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">pH:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2755585R1414157" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">6</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002755885R1415153" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Glucose:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2755885R1415158" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2755885R1415158_0" type="radio" name="rdo2755885R1415158" value="NEGATIVE" checked="checked" /><label for="rdo2755885R1415158_0">Negative</label></td><td><input id="rdo2755885R1415158_1" type="radio" name="rdo2755885R1415158" value="POSITIVE" /><label for="rdo2755885R1415158_1">Positive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002755985R1416154" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Protein:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2755985R1416159" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2755985R1416159_0" type="radio" name="rdo2755985R1416159" value="NEGATIVE" checked="checked" /><label for="rdo2755985R1416159_0">Negative</label></td><td><input id="rdo2755985R1416159_1" type="radio" name="rdo2755985R1416159" value="POSITIVE" /><label for="rdo2755985R1416159_1">Positive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002755785R1417155" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Bilirubin:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2755785R1417160" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2755785R1417160_0" type="radio" name="rdo2755785R1417160" value="NEGATIVE" checked="checked" /><label for="rdo2755785R1417160_0">Negative</label></td><td><input id="rdo2755785R1417160_1" type="radio" name="rdo2755785R1417160" value="POSITIVE" /><label for="rdo2755785R1417160_1">Positive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002755685R1418156" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Ketones:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2755685R1418161" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2755685R1418161_0" type="radio" name="rdo2755685R1418161" value="NEGATIVE" checked="checked" /><label for="rdo2755685R1418161_0">Negative</label></td><td><input id="rdo2755685R1418161_1" type="radio" name="rdo2755685R1418161" value="POSITIVE" /><label for="rdo2755685R1418161_1">Positive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002942285R1419157" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Leucocytes:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2942285R1419162" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2942285R1419162_0" type="radio" name="rdo2942285R1419162" value="PRESENT" /><label for="rdo2942285R1419162_0">Present</label></td><td><input id="rdo2942285R1419162_1" type="radio" name="rdo2942285R1419162" value="ABSENT" checked="checked" /><label for="rdo2942285R1419162_1">Absent</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002756085R14110158" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Blood:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2756085R14110163" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2756085R14110163_0" type="radio" name="rdo2756085R14110163" value="NEGATIVE" checked="checked" /><label for="rdo2756085R14110163_0">Negative</label></td><td><input id="rdo2756085R14110163_1" type="radio" name="rdo2756085R14110163" value="POSITIVE" /><label for="rdo2756085R14110163_1">Positive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002911585R14111159" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Red Cells (RBCs):</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2911585R14111164" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">0.3</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2911585R14111164" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">/HPF</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002911785R14112160" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">WBC:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2911785R14112165" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">2.6</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM2911785R14112165" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">/HPF</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002756185R14113161" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Casts:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2756185R14113166" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2756185R14113166_0" type="radio" name="rdo2756185R14113166" value="PRESENT" /><label for="rdo2756185R14113166_0">Present</label></td><td><input id="rdo2756185R14113166_1" type="radio" name="rdo2756185R14113166" value="ABSENT" checked="checked" /><label for="rdo2756185R14113166_1">Absent</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002917685R14114162" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Overall Assessment:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2917685R14114167" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2917685R14114167_0" type="radio" name="rdo2917685R14114167" value="NORMAL" /><label for="rdo2917685R14114167_0">Normal</label></td><td><input id="rdo2917685R14114167_1" type="radio" name="rdo2917685R14114167" value="ABNORMAL NCS" checked="checked" /><label for="rdo2917685R14114167_1">Abnormal NCS</label></td><td><input id="rdo2917685R14114167_2" type="radio" name="rdo2917685R14114167" value="ABNORMAL CS" /><label for="rdo2917685R14114167_2">Abnormal CS</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0100900002917785R14115163" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Abnormal CS, Please specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2917785R14115168" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2764985R14116169" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If any parameter 'Abnormal CS', captured abnormality in ‘Medical/Surgical History form’</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="ADDITIONAL LABORATORY DATA -URINE ANALYSIS" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;ADDITIONAL LABORATORY DATA -URINE ANALYSIS</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000254341145R1211164" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of urine Sample Collected:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd254341145R1211170" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000259151145R1212165" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Appearance:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt259151145R1212171" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Clear</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000254351145R1213166" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Color:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt254351145R1213172" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Pale Yellow</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000254701145R1214167" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Nitrite:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo254701145R1214173" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo254701145R1214173_0" type="radio" name="rdo254701145R1214173" value="NEGATIVE" checked="checked" /><label for="rdo254701145R1214173_0">Negative</label></td><td><input id="rdo254701145R1214173_1" type="radio" name="rdo254701145R1214173" value="POSITIVE" /><label for="rdo254701145R1214173_1">Positive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk008820000254711145R1215168" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Urobilinogen:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo254711145R1215174" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo254711145R1215174_0" type="radio" name="rdo254711145R1215174" value="NORMAL" checked="checked" /><label for="rdo254711145R1215174_0">Normal</label></td><td><input id="rdo254711145R1215174_1" type="radio" name="rdo254711145R1215174" value="ABNORMAL" /><label for="rdo254711145R1215174_1">Abnormal</label></td><td></td>
	</tr>
</table></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="IMMUNOLOGICAL ASSESSMENT" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;IMMUNOLOGICAL ASSESSMENT</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0088300002550044R1511169" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Sample collected?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2550044R1511175" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2550044R1511175_0" type="radio" name="rdo2550044R1511175" value="YES" checked="checked" /><label for="rdo2550044R1511175_0">Yes</label></td><td><input id="rdo2550044R1511175_1" type="radio" name="rdo2550044R1511175" value="NO" /><label for="rdo2550044R1511175_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0088300002913344R1512170" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of sample collection:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2913344R1512176" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0088300002963244R1513171" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">HIV:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2963244R1513177" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2963244R1513177_0" type="radio" name="rdo2963244R1513177" value="NEGATIVE" checked="checked" /><label for="rdo2963244R1513177_0">Negative</label></td><td><input id="rdo2963244R1513177_1" type="radio" name="rdo2963244R1513177" value="POSITIVE" /><label for="rdo2963244R1513177_1">Positive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0088300002963144R1514172" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">HCV:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2963144R1514178" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2963144R1514178_0" type="radio" name="rdo2963144R1514178" value="NON-REACTIVE" checked="checked" /><label for="rdo2963144R1514178_0">Non-Reactive</label></td><td><input id="rdo2963144R1514178_1" type="radio" name="rdo2963144R1514178" value="REACTIVE" /><label for="rdo2963144R1514178_1">Reactive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0088300002886744R1515173" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">HBsAg:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2886744R1515179" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2886744R1515179_0" type="radio" name="rdo2886744R1515179" value="NON-REACTIVE" checked="checked" /><label for="rdo2886744R1515179_0">Non-Reactive</label></td><td><input id="rdo2886744R1515179_1" type="radio" name="rdo2886744R1515179" value="REACTIVE" /><label for="rdo2886744R1515179_1">Reactive</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0088300002627744R1516174" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Overall Assessment:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2627744R1516180" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2627744R1516180_0" type="radio" name="rdo2627744R1516180" value="NORMAL" checked="checked" /><label for="rdo2627744R1516180_0">Normal</label></td><td><input id="rdo2627744R1516180_1" type="radio" name="rdo2627744R1516180" value="ABNORMAL NCS" /><label for="rdo2627744R1516180_1">Abnormal NCS</label></td><td><input id="rdo2627744R1516180_2" type="radio" name="rdo2627744R1516180" value="ABNORMAL CS" /><label for="rdo2627744R1516180_2">Abnormal CS</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0088300002816144R1517175" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Abnormal CS, Please specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2816144R1517181" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2816444R1518182" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If any of the Laboratory parameter found “Abnormal Clinically Significant” then capture the details in “Medical/Surgical History."</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="ECOG PERFORMANCE STATUS" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;ECOG PERFORMANCE STATUS</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0016900002698686R1611176" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">ECOG performed?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2698686R1611183" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2698686R1611183_0" type="radio" name="rdo2698686R1611183" value="YES" checked="checked" /><label for="rdo2698686R1611183_0">Yes</label></td><td><input id="rdo2698686R1611183_1" type="radio" name="rdo2698686R1611183" value="NO" /><label for="rdo2698686R1611183_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0016900003019386R1612177" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of ECOG performed:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd3019386R1612184" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0016900002644486R1613178" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">ECOG Criteria:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2644486R1613185" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2644486R1613185_0" type="radio" name="rdo2644486R1613185" value="0" checked="checked" /><label for="rdo2644486R1613185_0">0</label></td><td><input id="rdo2644486R1613185_1" type="radio" name="rdo2644486R1613185" value="1" /><label for="rdo2644486R1613185_1">1</label></td><td><input id="rdo2644486R1613185_2" type="radio" name="rdo2644486R1613185" value="2" /><label for="rdo2644486R1613185_2">2</label></td>
	</tr><tr>
		<td><input id="rdo2644486R1613185_3" type="radio" name="rdo2644486R1613185" value="3" /><label for="rdo2644486R1613185_3">3</label></td><td><input id="rdo2644486R1613185_4" type="radio" name="rdo2644486R1613185" value="4" /><label for="rdo2644486R1613185_4">4</label></td><td><input id="rdo2644486R1613185_5" type="radio" name="rdo2644486R1613185" value="5" /><label for="rdo2644486R1613185_5">5</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2644586R1614186" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">0=Fully active,able to carry on all pre-disease performance without restriction.</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2644686R1615187" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">1=Restricted in physically strenuous activity but ambulatory and able to carry out work of a light or sedentary nature,e.g.light housework,officework.</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2644786R1616188" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">2=Ambulatory and capable of all self-care but unable to carry out any work activities.Up and about more than 50% of waking hours.</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2644886R1617189" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">3=Capable of only limited self care,confined to bed or chair more than 50% of waking hours.</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2644986R1618190" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">4=Completely disabled.Cannot carry on any self-care.Totally confined to bed or chair.</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2645086R1619191" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">5=Dead</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2645286R16110192" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If ECOG is 3 to 5 then patient is not eligible to participate in the study and fill the final status form.</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="RADIOLOGICAL INVESTIGATION" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;RADIOLOGICAL INVESTIGATION</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0019900002487687R1711179" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Radiological investigation performed?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2487687R1711193" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2487687R1711193_0" type="radio" name="rdo2487687R1711193" value="YES" checked="checked" /><label for="rdo2487687R1711193_0">Yes</label></td><td><input id="rdo2487687R1711193_1" type="radio" name="rdo2487687R1711193" value="NO" /><label for="rdo2487687R1711193_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0019900003019287R1712180" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of investigation:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd3019287R1712194" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0019900002454787R1713181" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Investigation done:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="chk2454787R1713195" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="chk2454787R1713195_0" type="checkbox" name="chk2454787R1713195$0" checked="checked" /><label for="chk2454787R1713195_0">CT SCAN</label></td><td><input id="chk2454787R1713195_1" type="checkbox" name="chk2454787R1713195$1" /><label for="chk2454787R1713195_1">MRI</label></td><td><input id="chk2454787R1713195_2" type="checkbox" name="chk2454787R1713195$2" /><label for="chk2454787R1713195_2">OTHER</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0019900002455087R1714182" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If 'Other',please specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2455087R1714196" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="EVALUATION OF TARGET LESION" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;EVALUATION OF TARGET LESION</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk010010000274381150R1811183" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Sum of the diameter:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt274381150R1811197" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">85.0</span>&nbsp;&nbsp;&nbsp;<span id="LabUOM274381150R1811197" style="font-family:'Times New Roman' !Important;font-size:12px !Important;font-weight:bold !Important;">mm</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="BONE SCAN" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;BONE SCAN</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0019900002455188R1711184" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Bone scan performed?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2455188R1711198" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2455188R1711198_0" type="radio" name="rdo2455188R1711198" value="YES" /><label for="rdo2455188R1711198_0">Yes</label></td><td><input id="rdo2455188R1711198_1" type="radio" name="rdo2455188R1711198" value="NO" checked="checked" /><label for="rdo2455188R1711198_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0019900003019288R1712185" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of bone scan:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd3019288R1712199" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0019900002455388R1713186" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Provide lesion description:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txta2455388R1713200" style="font-family:'Times New Roman' !Important;font-size:12px !Important;word-wrap:break-word;white-space:none;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2484188R1714201" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: Bone scan may need to be repeated in following conditions: When progression in bone is clinically suspected or To confirm CR when the bone scan at screening visit is suggestive of bone metastasis and in subsequent scans CR is identified in target and other non-target lesions.</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="SERUM PREGNANCY TEST" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;SERUM PREGNANCY TEST</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0051700003012942R1911187" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Serum Pregnancy test performed?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo3012942R1911202" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo3012942R1911202_0" type="radio" name="rdo3012942R1911202" value="YES" checked="checked" /><label for="rdo3012942R1911202_0">Yes</label></td><td><input id="rdo3012942R1911202_1" type="radio" name="rdo3012942R1911202" value="NO" /><label for="rdo3012942R1911202_1">No</label></td><td><input id="rdo3012942R1911202_2" type="radio" name="rdo3012942R1911202" value="NAP" /><label for="rdo3012942R1911202_2">NAP</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0051700002915442R1912188" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of sample collection:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2915442R1912203" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">25-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0051700001731342R1913189" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Result of serum Pregnancy Test:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo1731342R1913204" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo1731342R1913204_0" type="radio" name="rdo1731342R1913204" value="POSITIVE" /><label for="rdo1731342R1913204_0">Positive</label></td><td><input id="rdo1731342R1913204_1" type="radio" name="rdo1731342R1913204" value="NEGATIVE" checked="checked" /><label for="rdo1731342R1913204_1">Negative</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl1731442R1914205" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If subject is surgically sterile (at least 6 month prior to study drug administration) or post-menopausal (at least 12 consecutive month) then, select 'NAP'. If Result is Positive then patient is not eligible to participate in the study and fill the final status form.</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="ECHOCARDIOGRAPHY" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;ECHOCARDIOGRAPHY</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0091500002669189R2011190" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">ECHO test performed?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2669189R2011206" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2669189R2011206_0" type="radio" name="rdo2669189R2011206" value="YES" checked="checked" /><label for="rdo2669189R2011206_0">Yes</label></td><td><input id="rdo2669189R2011206_1" type="radio" name="rdo2669189R2011206" value="NO" /><label for="rdo2669189R2011206_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0091500002972989R2012191" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of assessment:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd2972989R2012207" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">26-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0091500002963389R2013192" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Left ventricular ejection fraction [LVEF] >=50%:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2963389R2013208" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2963389R2013208_0" type="radio" name="rdo2963389R2013208" value="YES" checked="checked" /><label for="rdo2963389R2013208_0">Yes</label></td><td><input id="rdo2963389R2013208_1" type="radio" name="rdo2963389R2013208" value="NO" /><label for="rdo2963389R2013208_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0091500002608389R2014193" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Interpretation:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2608389R2014209" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2608389R2014209_0" type="radio" name="rdo2608389R2014209" value="NORMAL" checked="checked" /><label for="rdo2608389R2014209_0">Normal</label></td><td><input id="rdo2608389R2014209_1" type="radio" name="rdo2608389R2014209" value="ABNORMAL NCS" /><label for="rdo2608389R2014209_1">Abnormal NCS</label></td><td><input id="rdo2608389R2014209_2" type="radio" name="rdo2608389R2014209" value="ABNORMAL CS" /><label for="rdo2608389R2014209_2">Abnormal CS</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0091500002608589R2015194" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Please specify, If Abnormal CS:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2608589R2015210" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2668889R2016211" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If Interpretation is marked as Abnormal CS then capture details in Medical/surgical history. If Left ventricular ejection fraction is Less then 50% then fill the final status form</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="ELECTROCARDIOGRAM" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;ELECTROCARDIOGRAM</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0052100002540390R2111195" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">ECG Performed?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2540390R2111212" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2540390R2111212_0" type="radio" name="rdo2540390R2111212" value="YES" checked="checked" /><label for="rdo2540390R2111212_0">Yes</label></td><td><input id="rdo2540390R2111212_1" type="radio" name="rdo2540390R2111212" value="NO" /><label for="rdo2540390R2111212_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0052100003013090R2112196" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Date of Assessment:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txtd3013090R2112213" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">26-Jun-2018</span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0052100002540490R2113197" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Interpretation:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2540490R2113214" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2540490R2113214_0" type="radio" name="rdo2540490R2113214" value="NORMAL" checked="checked" /><label for="rdo2540490R2113214_0">Normal</label></td><td><input id="rdo2540490R2113214_1" type="radio" name="rdo2540490R2113214" value="ABNORMAL NCS" /><label for="rdo2540490R2113214_1">Abnormal NCS</label></td><td><input id="rdo2540490R2113214_2" type="radio" name="rdo2540490R2113214" value="ABNORMAL CS" /><label for="rdo2540490R2113214_2">Abnormal CS</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0052100002221090R2114198" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If Abnormal CS, Please specify:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT>&nbsp;&nbsp;<span id="txt2221090R2114215" disabled="disabled" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;"></span></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl1739490R2115216" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If Abnormal-CS then capture the abnormality in the "MEDICAL/SURGICAL HISTORY".</span></Td></Tr></Tr></Table></Td></Tr><Tr ALIGN=LEFT><Td style="vertical-align:top;"><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr data-bookmark-enabled="true" data-bookmark-level="2"  data-bookmark-text="INCLUSION/EXCLUSION CRITERIA" width="100%" color:#FFFFFF; ALIGN=LEFT style="BACKGROUND-COLOR: #008ecd; page-break-inside:avoid;"><Td style="vertical-align:middle;color:#FFFFFF;  width: 80%;">&nbsp;INCLUSION/EXCLUSION CRITERIA</Td></Tr></Table><Tr><td><Table width="100%" cellspacing='0' style="font-family:'Times New Roman' !Important; font-size:12px; border-collapse: collapse !Important;"><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0089400002577833R2211199" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Subject met all inclusion criteria?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2577833R2211217" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2577833R2211217_0" type="radio" name="rdo2577833R2211217" value="YES" /><label for="rdo2577833R2211217_0">Yes</label></td><td><input id="rdo2577833R2211217_1" type="radio" name="rdo2577833R2211217" value="NO" checked="checked" /><label for="rdo2577833R2211217_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0089400002592233R2212200" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If NO, list the INCLUSION criterion number(s) not met:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="chk2592233R2212218" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="chk2592233R2212218_0" type="checkbox" name="chk2592233R2212218$0" /><label for="chk2592233R2212218_0">1</label></td><td><input id="chk2592233R2212218_1" type="checkbox" name="chk2592233R2212218$1" /><label for="chk2592233R2212218_1">2</label></td><td><input id="chk2592233R2212218_2" type="checkbox" name="chk2592233R2212218$2" checked="checked" /><label for="chk2592233R2212218_2">3</label></td>
	</tr><tr>
		<td><input id="chk2592233R2212218_3" type="checkbox" name="chk2592233R2212218$3" checked="checked" /><label for="chk2592233R2212218_3">4</label></td><td><input id="chk2592233R2212218_4" type="checkbox" name="chk2592233R2212218$4" /><label for="chk2592233R2212218_4">5</label></td><td><input id="chk2592233R2212218_5" type="checkbox" name="chk2592233R2212218$5" /><label for="chk2592233R2212218_5">6</label></td>
	</tr><tr>
		<td><input id="chk2592233R2212218_6" type="checkbox" name="chk2592233R2212218$6" /><label for="chk2592233R2212218_6">7</label></td><td><input id="chk2592233R2212218_7" type="checkbox" name="chk2592233R2212218$7" /><label for="chk2592233R2212218_7">8</label></td><td><input id="chk2592233R2212218_8" type="checkbox" name="chk2592233R2212218$8" /><label for="chk2592233R2212218_8">9</label></td>
	</tr><tr>
		<td><input id="chk2592233R2212218_9" type="checkbox" name="chk2592233R2212218$9" /><label for="chk2592233R2212218_9">10</label></td><td><input id="chk2592233R2212218_10" type="checkbox" name="chk2592233R2212218$10" /><label for="chk2592233R2212218_10">11</label></td><td><input id="chk2592233R2212218_11" type="checkbox" name="chk2592233R2212218$11" /><label for="chk2592233R2212218_11">12</label></td>
	</tr><tr>
		<td><input id="chk2592233R2212218_12" type="checkbox" name="chk2592233R2212218$12" /><label for="chk2592233R2212218_12">13</label></td><td><input id="chk2592233R2212218_13" type="checkbox" name="chk2592233R2212218$13" /><label for="chk2592233R2212218_13">14</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0089400002578133R2213201" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">Subject met any exclusion criteria?:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="rdo2578133R2213219" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="rdo2578133R2213219_0" type="radio" name="rdo2578133R2213219" value="YES" checked="checked" /><label for="rdo2578133R2213219_0">Yes</label></td><td><input id="rdo2578133R2213219_1" type="radio" name="rdo2578133R2213219" value="NO" /><label for="rdo2578133R2213219_1">No</label></td><td></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td width="60%" style="  font-family:'Times New Roman' !Important; font-size:12px;  vertical-align:middle; border: solid 1px gray !important; " ALIGN=LEFT>&nbsp;<span id="Lnk0089400002578733R2214202" style="word-wrap:break-word;white-space:;font-family:'Times New Roman' !Important;font-size:12px !Important;">If YES, list the EXCLUSION criterion number(s) met:</span></Td><Td width="40%" style="vertical-align:middle; font-family:'Times New Roman' !Important; font-size:12px; border: solid 1px gray !important;" ALIGN=LEFT><table id="chk2578733R2214220" border="0" style="font-family:'Times New Roman' !Important;font-size:12px !Important;">
	<tr>
		<td><input id="chk2578733R2214220_0" type="checkbox" name="chk2578733R2214220$0" /><label for="chk2578733R2214220_0">1</label></td><td><input id="chk2578733R2214220_1" type="checkbox" name="chk2578733R2214220$1" checked="checked" /><label for="chk2578733R2214220_1">2</label></td><td><input id="chk2578733R2214220_2" type="checkbox" name="chk2578733R2214220$2" /><label for="chk2578733R2214220_2">3</label></td>
	</tr><tr>
		<td><input id="chk2578733R2214220_3" type="checkbox" name="chk2578733R2214220$3" /><label for="chk2578733R2214220_3">4</label></td><td><input id="chk2578733R2214220_4" type="checkbox" name="chk2578733R2214220$4" /><label for="chk2578733R2214220_4">5</label></td><td><input id="chk2578733R2214220_5" type="checkbox" name="chk2578733R2214220$5" /><label for="chk2578733R2214220_5">6</label></td>
	</tr><tr>
		<td><input id="chk2578733R2214220_6" type="checkbox" name="chk2578733R2214220$6" /><label for="chk2578733R2214220_6">7</label></td><td><input id="chk2578733R2214220_7" type="checkbox" name="chk2578733R2214220$7" /><label for="chk2578733R2214220_7">8</label></td><td><input id="chk2578733R2214220_8" type="checkbox" name="chk2578733R2214220$8" /><label for="chk2578733R2214220_8">9</label></td>
	</tr><tr>
		<td><input id="chk2578733R2214220_9" type="checkbox" name="chk2578733R2214220$9" /><label for="chk2578733R2214220_9">10</label></td><td><input id="chk2578733R2214220_10" type="checkbox" name="chk2578733R2214220$10" /><label for="chk2578733R2214220_10">11</label></td><td><input id="chk2578733R2214220_11" type="checkbox" name="chk2578733R2214220$11" /><label for="chk2578733R2214220_11">12</label></td>
	</tr>
</table></Td></Tr></Tr><Tr ALIGN=LEFT style="page-break-inside:avoid;"><Td colspan="2" style=" !important; vertical-align:middle; border:1px solid gray !Important;" ALIGN=LEFT><span id="lbl2578633R2215221" class="Label" style="word-wrap:break-word;white-space:none;font-family:'Times New Roman' !Important;font-size:12px !Important;">Note: If 'No' for any 'Inclusion criteria' and 'Yes' for any 'Exclusion criteria', then do not include the subject in the study and fill 'Final Status Form'.</span></Td></Tr></Tr></Table></Td></Tr></Table>










headercontent += "<html><head></head><body>";
				headercontent += "<table style=\"margin-top: 2px; margin: auto; border: solid 1px black; width: 100%; font-family:'Times New Roman'; font-size:12px; \"align=\"left\">";
				headercontent += "<tr style=\" \">";
				headercontent += "<td valign=\"top\">";
				headercontent += "<table style=\"font-family: 'Times New Roman'; font-size:12px; \">";
				headercontent += "<tr style=\" \">";
				headercontent += "<td colspan=\"4\">";
				headercontent += "<Label  for \"" + ConfigurationManager.AppSettings["Client"].ToString() + "\">" + ConfigurationManager.AppSettings["Client"].ToString() + "</asp:Label>";
				headercontent += "</td>";
				headercontent += "</tr>";
				headercontent += "<tr style=\" \">";
				headercontent += "<td colspan=\"4\">";
				headercontent += "Sponsor Name:<Label  for \"" + ds_header.Tables[0].Rows[0]["vClientName"].ToString() + "\">" + ds_header.Tables[0].Rows[0]["vClientName"].ToString() + "</asp:Label>";
				headercontent += "</td>";
				headercontent += "</tr >";
				headercontent += "<tr style=\" \">";
				headercontent += "<td align=\"right\" colspan=\"4\" >";
				headercontent += "<h4>";
				headercontent += "CASE REPORT FORM</h4>";
				headercontent += "</td>";
				headercontent += "</tr>";
				headercontent += "<tr style=\" \">";
				headercontent += "<td align=\"right\">Project No:</td>";
				headercontent += "<td style=\"border: thin solid #000000;\">";
				headercontent += "<Label  for \"" + ProjectNo + "\">" + ProjectNo + "</asp:Label>";
				headercontent += "</td>";
				if (Convert.ToBoolean(this.ViewState[IsProjectCT]) == true)
				{
					headercontent += "<td align=\"right\">Site Id:</td>";
					headercontent += "<td  style=\"border: thin solid #000000;\">";
					headercontent += "<Label  for \"" + SiteId.ToString() + "\">" + SiteId.ToString() + "</asp:Label>";
					headercontent += "</td>";
				}
				if (this.chkprotocolno.Checked == false)
				{
					if (ds_header.Tables[0].Rows[0]["ProtocolNo"].ToString().Trim().Length > 0)
					{
						headercontent += "<td align=\"right\">Protocol No:</td>";
						headercontent += "<td  style=\"border: thin solid #000000;\">";
						headercontent += "<Label  for \"" + ds_header.Tables[0].Rows[0]["ProtocolNo"].ToString().Trim() + "\">" + ds_header.Tables[0].Rows[0]["ProtocolNo"].ToString().Trim() + "</asp:Label>";
						headercontent += "</td>";
					}
				}
				headercontent += "</tr>";
				headercontent += "<tr style=\" \">";
				if (Convert.ToBoolean(this.ViewState[IsProjectCT]))
				{
					headercontent += "<td align=\"right\">Subject No:</td>";
					headercontent += "<td style=\"border: thin solid #000000;\">";
					headercontent += "<Label  for \"" + SubjectNo + "\">" + SubjectNo + "</asp:Label>";
					headercontent += "</td>";
					if (this.chkinitial.Checked == false)
					{
						headercontent += "<td align=\"right\">Subject Initials:</td>";
						headercontent += "<td  style=\"border: thin solid #000000;\">";
						headercontent += "<Label  for \"" + SubjectInitial + "\">" + SubjectInitial + "</asp:Label>";
						headercontent += "</td>";
					}
				}
				else
				{
					headercontent += "<td align=\"right\">Subject No:</td>";
					headercontent += "<td style=\"border: thin solid #000000;\">";
					headercontent += "<Label  for \"" + SubjectNo + "\">" + SubjectNo + "</asp:Label>";
					headercontent += "</td>";
					if (this.chkinitial.Checked == false)
					{
						headercontent += "<td align=\"right\">Subject Initials:</td>";
						headercontent += "<td  style=\"border: thin solid #000000;\">";
						headercontent += "<Label  for \"" + SubjectInitial + "\">" + SubjectInitial + "</asp:Label>";
						headercontent += "</td>";
					}
				}
				headercontent += "</tr>";
				headercontent += "</table>";
				headercontent += "</td>";
				if (!string.IsNullOrEmpty(this.ViewState[vs_sponsorlogofilepath].ToString().Trim()))
				{
					headercontent += "<td valign=\"middle\">";
					headercontent += "<img id=ctl00_CPHLAMBDA_ImgsponsorLogo alt=\"" + this.ViewState[vs_sponsorlogofilepath].ToString() + "\" src=\"" + this.ViewState[vs_sponsorlogofilepath].ToString() + "\"right\" alt=\"lambda\" style=\"width:120px; height:120px;\"/>";
					headercontent += "</td>";
				}
				headercontent += "<td valign=\"middle\">";
				headercontent += "<img id=ctl00_CPHLAMBDA_ImgLogo alt=\"" + Path.ToString() + "\" src=\"" + Path.ToString() + "\"right\" alt=\"lambda\" style=\"width:120px; height:120px;\"/>";
				headercontent += "</td>";
				headercontent += "</tr>";
				headercontent += "</table>";
				headercontent += "</body></html>";









PdfDocument pdfDocument = new PdfDocument();

// Create a PDF page instance
PdfPageBase page = pdfDocument.Pages.Add();

// Create an HTML to PDF element for the header
HtmlToPdfElement Header1 = new HtmlToPdfElement(headercontent, string.Empty);

// Set the width of the HTML viewer based on selected orientation
if (ddlOrientation.SelectedValue.ToString().ToUpper().ToString() == "A4")
{
    Header1.HtmlViewerWidth = 662; // Previous 750, 647
}
else if (ddlOrientation.SelectedValue.ToString().ToUpper().ToString() == "LETTER")
{
    Header1.HtmlViewerWidth = 684; // Previous 750, 647
}

// Disable fitting the width of the header to the page width
Header1.FitWidth = false;

// Add the header element to the PDF header
page.Header = Header1;

// Set up table of contents options
pdfDocument.TableOfContents.Enabled = true;
pdfDocument.TableOfContents.Title = "Table of Contents";

// Set up table of contents styles for level 1
PdfTocStyle tocStyle = pdfDocument.TableOfContents[0];
tocStyle.Level1Style = new PdfTocTextStyle(new PdfFont(PdfFontFamily.Helvetica, 16), Color.Black, true, true);

// Add authenticated information to PDF footer if available
if (!string.IsNullOrEmpty(hdnSubSelection.Value.Trim()))
{
    PdfPageTemplateElement footer = new PdfPageTemplateElement(page.Graphics.ClientSize.Width, 30);
    footer.Foreground = true;

    // Add authenticated by and authenticated on information
    PdfFont pdfFont = new PdfFont(PdfFontFamily.Helvetica, 10);
    footer.Graphics.DrawString("[Authenticated By:" + (Session[VS_AuthenticatedBy] == null ? null : Convert.ToString(Session[VS_AuthenticatedBy])) + "]", pdfFont, PdfBrushes.Black, new PointF(0, 15));
    footer.Graphics.DrawString("[Authenticated On:" + (Session[VS_AuthenticatedOn] == null ? null : Convert.ToString(Session[VS_AuthenticatedOn])) + "]", pdfFont, PdfBrushes.Black, new PointF(0, 28));

    // Add footer text with disclaimer and placeholders for page numbers
    PdfPageNumberField pageNumber = new PdfPageNumberField();
    PdfPageCountField pageCount = new PdfPageCountField();
    PdfCompositeField compositeField = new PdfCompositeField(pdfFont, PdfBrushes.Black, "*This is an electronically authenticated report.                                            Page {0} of {1}", pageNumber, pageCount);
    compositeField.StringFormat = new PdfStringFormat(PdfTextAlignment.Right);
    compositeField.Bounds = footer.Bounds;
    compositeField.Draw(footer.Graphics);

    // Add the footer to the PDF page
    page.Footer = footer;
}

// Set htmlcontent to a value stored in HFHeaderLabel
htmlcontent = this.HFHeaderLabel.Value.ToString();

// Disable a button named BtnGeneratePdf
BtnGeneratePdf.Enabled = false;








 HtmlToPdfElement Header1 = new HtmlToPdfElement(headercontent, string.Empty);
                if (ddlOrientation.SelectedValue.ToString().ToUpper().ToString() == "A4")
                {
                    Header1.HtmlViewerWidth = 662; //'Previous 750, 647
                }
                else if (ddlOrientation.SelectedValue.ToString().ToUpper().ToString() == "LETTER")
                {
                    Header1.HtmlViewerWidth = 684; //'Previous 750, 647
                }
                Header1.FitWidth = false;
                pdfconverter.PdfHeaderOptions.AddElement(Header1);

                pdfconverter.TableOfContentsOptions.AutoTocItemsEnabled = true;
                string level1TextStyle = "font-family:'Times New Roman'; font-size:16px; text-decoration: underline;";
                pdfconverter.TableOfContentsOptions.SetItemStyle(1, level1TextStyle);

                string level1PageNumberStyle = "padding-right:3px; font-family:'Times New Roman'; font-size:16px; text-decoration: underline; font-weight:bold";
                pdfconverter.TableOfContentsOptions.SetPageNumberStyle(1, level1PageNumberStyle);

                if (!string.IsNullOrEmpty(hdnSubSelection.Value.Trim()))
                {
                    pdfconverter.PdfFooterOptions.AddElement(new TextElement(0, 15, "[Authenticated By:" + (Session[VS_AuthenticatedBy] == null ? null : Convert.ToString(Session[VS_AuthenticatedBy])) + "]", pdfFont));
                    pdfconverter.PdfFooterOptions.AddElement(new TextElement(0, 28, "[Authenticated On:" + (Session[VS_AuthenticatedOn] == null ? null : Convert.ToString(Session[VS_AuthenticatedOn])) + "]", pdfFont));
                }

                pdfconverter.PdfFooterOptions.PageNumberingStartIndex = 0;
                pdfconverter.PdfFooterOptions.AddElement(new LineElement(0, 0, pdfconverter.PdfDocumentOptions.PdfPageSize.Width - pdfconverter.PdfDocumentOptions.LeftMargin - pdfconverter.PdfDocumentOptions.RightMargin, 0));
                TextElement footerText = new TextElement(0, 1, "*This is an electronically authenticated report.                                            Page &p; of &P;                       ", new Font(new FontFamily("Times New Roman"), 12, GraphicsUnit.Point));
                footerText.TextAlign = HorizontalTextAlign.Right;
                footerText.ForeColor = Color.Navy;
                footerText.EmbedSysFont = true;
                pdfconverter.PdfFooterOptions.AddElement(footerText);

                htmlcontent = this.HFHeaderLabel.Value.ToString();
                BtnGeneratePdf.Enabled = false;












 HtmlToPdfElement Header1 = new HtmlToPdfElement(headercontent, string.Empty);
                if (ddlOrientation.SelectedValue.ToString().ToUpper().ToString() == "A4")
                {
                    Header1.HtmlViewerWidth = 662; //'Previous 750, 647
                }
                else if (ddlOrientation.SelectedValue.ToString().ToUpper().ToString() == "LETTER")
                {
                    Header1.HtmlViewerWidth = 684; //'Previous 750, 647
                }
                Header1.FitWidth = false;
                pdfconverter.PdfHeaderOptions.AddElement(Header1);

                pdfconverter.TableOfContentsOptions.AutoTocItemsEnabled = true;
                string level1TextStyle = "font-family:'Times New Roman'; font-size:16px; text-decoration: underline;";
                pdfconverter.TableOfContentsOptions.SetItemStyle(1, level1TextStyle);

                string level1PageNumberStyle = "padding-right:3px; font-family:'Times New Roman'; font-size:16px; text-decoration: underline; font-weight:bold";
                pdfconverter.TableOfContentsOptions.SetPageNumberStyle(1, level1PageNumberStyle);

                if (!string.IsNullOrEmpty(hdnSubSelection.Value.Trim()))
                {
                    pdfconverter.PdfFooterOptions.AddElement(new TextElement(0, 15, "[Authenticated By:" + (Session[VS_AuthenticatedBy] == null ? null : Convert.ToString(Session[VS_AuthenticatedBy])) + "]", pdfFont));
                    pdfconverter.PdfFooterOptions.AddElement(new TextElement(0, 28, "[Authenticated On:" + (Session[VS_AuthenticatedOn] == null ? null : Convert.ToString(Session[VS_AuthenticatedOn])) + "]", pdfFont));
                }

                pdfconverter.PdfFooterOptions.PageNumberingStartIndex = 0;
                pdfconverter.PdfFooterOptions.AddElement(new LineElement(0, 0, pdfconverter.PdfDocumentOptions.PdfPageSize.Width - pdfconverter.PdfDocumentOptions.LeftMargin - pdfconverter.PdfDocumentOptions.RightMargin, 0));
                TextElement footerText = new TextElement(0, 1, "*This is an electronically authenticated report.                                            Page &p; of &P;                       ", new Font(new FontFamily("Times New Roman"), 12, GraphicsUnit.Point));
                footerText.TextAlign = HorizontalTextAlign.Right;
                footerText.ForeColor = Color.Navy;
                footerText.EmbedSysFont = true;
                pdfconverter.PdfFooterOptions.AddElement(footerText);

                htmlcontent = this.HFHeaderLabel.Value.ToString();
                BtnGeneratePdf.Enabled = false;







string htmlcontent = string.Empty;
        string headercontent = string.Empty;
        string data = string.Empty;
        ArrayList stylesheetarraylist = new ArrayList();
        System.Drawing.Font watermarkTextFont = null;
        string strProfileStatus = string.Empty;
        string wStr = string.Empty;
        string eStr = string.Empty;
        System.Drawing.Font pdfFont = null;
        DataSet ds_subject = new DataSet();
        DataSet ds_header = new DataSet();
        DataSet ds_SubSample = new DataSet();
        DataTable dt_subjectMain = new DataTable();
        DataView dv_subjectmain = null;
        string ScreeningHdrNo = string.Empty;
        string SubjId = "";
        string SubNo = "";
        string Initials = "";
        int NodeID = 0;
        string Gender = string.Empty;
        int indexrpt = 0;
        string StrRptNo = null;
        string project = null;
        string ProjectNo = null;
        string SiteId = null;
        string[] projects = null;
        string SubjectNo = null;
        string SubjectInitial = null;
        StrRptNo = "";
        SiteId = "";
        SubjectNo = "_";
        SubjectInitial = "_";
        DataTable dt_subjectcopy = new DataTable(); // Change from object to DataTable
        string strMappingRequired = "";
        string strdatetime = "";
        string[] DocumentsArray = null;
        string[] DocumentsArray1 = null;
        FileInfo fInfo = null;
        FileInfo fInfo1 = null;
        int ilabreport = 1;
        string strfilelogopath = "";
        string strsavelogopath = "";
        PdfDocument d2 = null;
        string SubIDForLab = string.Empty;
        string[] DocumentsArrayForMissingSubject = null;
        string[] DocumentsArrayZipFiles = null;
        int ExecuteDataOnlyonce = 0;
        int ExecuteDataOnlyonceMSR = 0;






string htmlcontent = string.Empty;
        string headercontent = string.Empty;
        PdfDocument d1 = null;
        string data = string.Empty;
        ArrayList stylesheetarraylist = new ArrayList();
        System.Drawing.Font watermarkTextFont = null;
        TextElement watermarkTextElement = null;
        string strProfileStatus = string.Empty;
        string wStr = string.Empty;
        string eStr = string.Empty;
        System.Drawing.Font pdfFont = null;
        DataSet ds_subject = new DataSet();
        DataSet ds_header = new DataSet();
        DataSet ds_SubSample = new DataSet();
        DataTable dt_subjectMain = new DataTable();
        DataView dv_subjectmain = null;
        string ScreeningHdrNo = string.Empty;
        string SubjId = "";
        string SubNo = "";
        string Initials = "";
        int NodeID = 0;
        string Gender = string.Empty;
        int indexrpt = 0;
        string StrRptNo = null;
        string project = null;
        string ProjectNo = null;
        string SiteId = null;
        string[] projects = null;
        string SubjectNo = null;
        string SubjectInitial = null;
        StrRptNo = "";
        SiteId = "";
        SubjectNo = "_";
        SubjectInitial = "_";
        object dt_subjectcopy = new DataTable();
        string strMappingRequired = "";
        string strdatetime = "";
        string[] DocumentsArray = null;
        string[] DocumentsArray1 = null;
        FileInfo fInfo = null;
        FileInfo fInfo1 = null;
        int ilabreport = 1;
        string strfilelogopath = "";
        string strsavelogopath = "";
        PdfDocument d2 = null;
        string SubIDForLab = string.Empty;
        string[] DocumentsArrayForMissingSubject = null;
        string[] DocumentsArrayZipFiles = null;
        int ExecuteDataOnlyonce = 0;
        int ExecuteDataOnlyonceMSR = 0;








// Assuming pdfConverter is an instance of Spire.Pdf.PdfDocument
PdfDocument pdfDocument = new PdfDocument();
pdfDocument.LoadFromFile("your_pdf_file_path.pdf");

if (ddlPrinttype.SelectedValue.ToUpper() == "DRAFT")
{
    // Create a watermark template
    PdfTemplate template = new PdfTemplate(300, 100);
    PdfTrueTypeFont font = new PdfTrueTypeFont(new Font("Times New Roman", 75, FontStyle.Bold), true);
    PdfBrush brush = PdfBrushes.Blue;
    template.Graphics.SetTransparency(20); // Setting opacity

    // Rotate the text element
    template.Graphics.RotateTransform(45);

    // Draw the text on the template
    template.Graphics.DrawString(strProfileStatus + " Draft Copy", font, brush, PointF.Empty);

    // Add the watermark to each page
    foreach (PdfPageBase page in pdfDocument.Pages)
    {
        page.Canvas.Save();
        page.Canvas.SetTransparency(20);
        page.Canvas.RotateTransform(45);
        page.Canvas.DrawTemplate(template, new PointF(50, 250));
        page.Canvas.Restore();
    }
}

// Save the modified PDF document
pdfDocument.SaveToFile("output_pdf_file_path.pdf");
pdfDocument.Close();









d1 = pdfconverter.ConvertHtmlToPdfDocumentObject(htmlcontent, string.Empty);
                if (this.ddlPrinttype.SelectedValue.ToUpper() == "DRAFT")
                {
                    watermarkTextFont = new System.Drawing.Font("Times New Roman", 75, FontStyle.Bold, GraphicsUnit.Point);
                    watermarkTextElement = new TextElement(50, 250, strProfileStatus + " Draft Copy", watermarkTextFont);
                    watermarkTextElement.ForeColor = System.Drawing.Color.Blue;
                    watermarkTextElement.Opacity = 20;
                    watermarkTextElement.TextAngle = 45;
                    foreach (Winnovative.PdfPage PdfPage in d1.Pages)
                    {
                        PdfPage.AddElement(watermarkTextElement);
                    }
                }



using Spire.Pdf;
using Spire.Pdf.Graphics;
using System;
using System.IO;

public bool FindBlankPage(ref string DocRemove, byte[] bytes)
{
    try
    {
        using (MemoryStream stream = new MemoryStream())
        {
            stream.Write(bytes, 0, bytes.Length);
            PdfDocumentBase doc = new PdfDocument();
            doc.LoadFromStream(stream);

            for (int i = 0; i < doc.Pages.Count; i++)
            {
                PdfPageBase page = doc.Pages[i];
                string text = page.ExtractText();

                if (string.IsNullOrWhiteSpace(text))
                {
                    DocRemove += i.ToString() + ",";
                }
            }
        }
        return true;
    }
    catch (Exception ex)
    {
        // Handle exceptions
        Console.WriteLine("Error: " + ex.Message);
        return false;
    }
}








 public bool FindBlankPage(ref string DocRemove, byte[] bytes)
	{
		try
		{
			iTextSharp.text.pdf.PdfReader oreader = new iTextSharp.text.pdf.PdfReader(bytes);
			using (MemoryStream stream = new MemoryStream())
			{
				iTextSharp.text.pdf.PdfReader reader = new iTextSharp.text.pdf.PdfReader(bytes);
				bytes = null;
				for (int i = 1; i <= reader.NumberOfPages; i++)
				{
					object sOut = "";
					iTextSharp.text.pdf.parser.LocationTextExtractionStrategy its = new iTextSharp.text.pdf.parser.LocationTextExtractionStrategy();
					sOut = iTextSharp.text.pdf.parser.PdfTextExtractor.GetTextFromPage(oreader, i, its);
					if (Convert.ToString(sOut) == "")
					{
						DocRemove += (i - 1).ToString() + ",";
					}
				}
				stream.Dispose();
			}
			return true;
		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "Error While Get Blank Page! ", ex);
			return false;
		}
		finally
		{
		}
	}



using Spire.Pdf;
using Spire.Pdf.Graphics;
using System;
using System.IO;

public bool GetBlankpage(ref PdfDocument d1, PdfDocument d2)
{
    string DocRemove = string.Empty;
    string[] DocRemove_arry = null;
    try
    {
        using (MemoryStream stream = new MemoryStream())
        {
            d2.SaveToStream(stream);
            PdfDocumentBase doc = new PdfDocument();
            doc.LoadFromStream(stream);

            for (int i = 0; i < doc.Pages.Count; i++)
            {
                PdfPageBase page = doc.Pages[i];
                string text = page.ExtractText();

                if (string.IsNullOrWhiteSpace(text))
                {
                    DocRemove += i.ToString() + ",";
                }
            }

            if (DocRemove.Length > 0)
            {
                DocRemove_arry = DocRemove.Substring(0, DocRemove.Length - 1).Split(',');
                for (int i = DocRemove_arry.Length - 1; i >= 0; i--)
                {
                    d1.Pages.RemoveAt(Convert.ToInt32(DocRemove_arry[i]));
                }
            }
        }
        return true;
    }
    catch (Exception ex)
    {
        // Handle exceptions
        Console.WriteLine("Error: " + ex.Message);
        return false;
    }
}





using Spire.Pdf;
using Spire.Pdf.Graphics;
using System;

public bool GetBlankpage(ref PdfDocument d1, PdfDocument d2)
{
    byte[] bytes = null;
    string DocRemove = string.Empty;
    string[] DocRemove_arry = null;
    try
    {
        bytes = d2.SaveToBytes();
        PdfDocumentBase doc = new PdfDocument();
        doc.LoadFromBytes(bytes);

        for (int i = 0; i < doc.Pages.Count; i++)
        {
            PdfPageBase page = doc.Pages[i];
            string text = page.ExtractText();

            if (string.IsNullOrWhiteSpace(text))
            {
                DocRemove += i.ToString() + ",";
            }
        }

        if (DocRemove.Length > 0)
        {
            DocRemove_arry = DocRemove.Substring(0, DocRemove.Length - 1).Split(',');
            for (int i = DocRemove_arry.Length - 1; i >= 0; i--)
            {
                d1.Pages.RemoveAt(Convert.ToInt32(DocRemove_arry[i]));
            }
        }
        return true;
    }
    catch (Exception ex)
    {
        // Handle exceptions
        Console.WriteLine("Error: " + ex.Message);
        return false;
    }
}








public bool GetBlankpage(ref Spire.Pdf.PdfDocument d1, Spire.Pdf.PdfDocument d2)
{
    byte[] bytes = null;
    string DocRemove = string.Empty;
    string[] DocRemove_arry = null;
    try
    {
        using (MemoryStream stream = new MemoryStream())
        {
            d2.SaveToStream(stream);
            bytes = stream.ToArray();

            using (Spire.Pdf.PdfDocumentBase document = new Spire.Pdf.PdfDocument())
            {
                document.LoadFromStream(stream);

                for (int i = 0; i < document.Pages.Count; i++)
                {
                    string sOut = "";
                    sOut = document.Pages[i].ExtractText();
                    if (string.IsNullOrEmpty(sOut.Trim()))
                    {
                        DocRemove += i.ToString() + ",";
                    }
                }
            }
        }

        if (!string.IsNullOrEmpty(DocRemove))
        {
            DocRemove_arry = DocRemove.TrimEnd(',').Split(',');
            for (int i = DocRemove_arry.Length - 1; i >= 0; i--)
            {
                d1.Pages.RemoveAt(Convert.ToInt32(DocRemove_arry[i]));
            }
        }
        return true;

    }
    catch (Exception ex)
    {
        // Handle exception
        return false;
    }
}








using System;
using System.Drawing;
using System.Web;
using Spire.Pdf;
using Spire.Pdf.Actions;
using Spire.Pdf.Annotations;
using Spire.Pdf.Bookmarks;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;

namespace practice6
{
    public partial class GeneratePdfWithToc : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePdf_Click(object sender, EventArgs e)
        {
            try
            {
                // Create a PDF document
                PdfDocument doc = new PdfDocument();
                doc.PageSettings.Size = PdfPageSize.A4;

                // Reset the default margins to 0
                doc.PageSettings.Margins = new PdfMargins(0);

                // Create a PdfMargins object for the page margins
                PdfMargins margins = new PdfMargins(60, 60, 60, 60);

                // Create a header template with content and apply it to the page template
                doc.Template.Top = CreateHeaderTemplate(doc, margins);

                // Apply blank templates to other parts of the page template
                doc.Template.Bottom = new PdfPageTemplateElement(doc.PageSettings.Size.Width, margins.Bottom);
                doc.Template.Left = new PdfPageTemplateElement(margins.Left, doc.PageSettings.Size.Height);
                doc.Template.Right = new PdfPageTemplateElement(margins.Right, doc.PageSettings.Size.Height);

                // Load a PDF document
                string fullPath = Server.MapPath("~/table.pdf");
                doc.LoadFromFile(fullPath);

                // Get the page count of the document
                int pageCount = doc.Pages.Count;

                // Insert a new page into the PDF document as the first page for TOC
                PdfPageBase tocPage = doc.Pages.Insert(0);

                // Draw TOC title on the new page
                string title = "Table of Contents";
                PdfTrueTypeFont titleFont = new PdfTrueTypeFont(new Font("Arial", 20, FontStyle.Bold));
                PdfStringFormat centerAlignment = new PdfStringFormat(PdfTextAlignment.Center, PdfVerticalAlignment.Middle);
                PointF location = new PointF(tocPage.Canvas.ClientSize.Width / 2, titleFont.MeasureString(title).Height + 10);
                tocPage.Canvas.DrawString(title, titleFont, PdfBrushes.CornflowerBlue, location, centerAlignment);

                // Draw TOC content on the new page
                PdfTrueTypeFont titlesFont = new PdfTrueTypeFont(new Font("Arial", 14));
                String[] titles = new String[pageCount];
                for (int i = 0; i < titles.Length; i++)
                {
                    titles[i] = string.Format("This is page {0}", i + 1);
                }
                float y = titleFont.MeasureString(title).Height + 10;
                float x = 0;

                // Draw page numbers of the target pages on the new page
                for (int i = 1; i <= pageCount; i++)
                {
                    string text = titles[i - 1];
                    SizeF titleSize = titlesFont.MeasureString(text);

                    PdfPageBase navigatedPage = doc.Pages[i];

                    string pageNumText = (i + 1).ToString();
                    SizeF pageNumTextSize = titlesFont.MeasureString(pageNumText);
                    tocPage.Canvas.DrawString(text, titlesFont, PdfBrushes.CadetBlue, 0, y);
                    float dotLocation = titleSize.Width + 2 + x;
                    float pageNumLocation = tocPage.Canvas.ClientSize.Width - pageNumTextSize.Width;
                    for (float j = dotLocation; j < pageNumLocation; j++)
                    {
                        if (dotLocation >= pageNumLocation)
                        {
                            break;
                        }
                        tocPage.Canvas.DrawString(".", titlesFont, PdfBrushes.Gray, dotLocation, y);
                        dotLocation += 3;
                    }
                    tocPage.Canvas.DrawString(pageNumText, titlesFont, PdfBrushes.CadetBlue, pageNumLocation, y);

                    // Add actions that will take you to the target pages when clicked on to the new page
                    location = new PointF(0, y);
                    RectangleF titleBounds = new RectangleF(location, new SizeF(tocPage.Canvas.ClientSize.Width, titleSize.Height));
                    PdfDestination dest = new PdfDestination(navigatedPage, new PointF(-doc.PageSettings.Margins.Top, -doc.PageSettings.Margins.Left));
                    PdfActionAnnotation action = new PdfActionAnnotation(titleBounds, new PdfGoToAction(dest));
                    action.Border = new PdfAnnotationBorder(0);
                    (tocPage as PdfNewPage).Annotations.Add(action);
                    y += titleSize.Height + 10;
                }

                // Save the PDF document
                string filePath = Server.MapPath("~/TableOfContents.pdf");
                doc.SaveToFile(filePath);
                doc.Close();
                Response.Write("PDF created successfully!");
            }
            catch (Exception ex)
            {
                Response.Write("PDF creation failed");
            }

        }

        static PdfPageTemplateElement CreateHeaderTemplate(PdfDocument doc, PdfMargins margins)
        {
            // Get page size
            SizeF pageSize = doc.PageSettings.Size;

            // Create a PdfPageTemplateElement object as header space
            PdfPageTemplateElement headerSpace = new PdfPageTemplateElement(pageSize.Width, margins.Top);
            headerSpace.Foreground = false;

            // Declare two float variables
            float x = margins.Left;
            float y = 0;

            // Draw image in header space 
            PdfImage headerImage = PdfImage.FromFile("logo.png");
            float width = headerImage.Width / 3;
            float height = headerImage.Height / 3;
            headerSpace.Graphics.DrawImage(headerImage, x, margins.Top - height - 2, width, height);

            // Draw line in header space
            PdfPen pen = new PdfPen(PdfBrushes.Gray, 1);
            headerSpace.Graphics.DrawLine(pen, x, y + margins.Top - 2, pageSize.Width - x, y + margins.Top - 2);

            // Draw text in header space
            PdfTrueTypeFont font = new PdfTrueTypeFont(new Font("Impact", 25f, FontStyle.Bold));
            PdfStringFormat format = new PdfStringFormat(PdfTextAlignment.Left);
            String headerText = "HEADER TEXT";
            SizeF size = font.MeasureString(headerText, format);
            headerSpace.Graphics.DrawString(headerText, font, PdfBrushes.Gray, pageSize.Width - x - size.Width - 2, margins.Top - (size.Height + 5), format);

            // Return headerSpace
            return headerSpace;
        }
    }
}








using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Spire.Pdf;
using Spire.Pdf.Actions;
using Spire.Pdf.Annotations;
using Spire.Pdf.Bookmarks;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;

namespace practice6
{
    public partial class GeneratePdfWithToc : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePdf_Click(object sender, EventArgs e)
        {
            try
            {
                // Initialize an instance of the PdfDocument class
                PdfDocument doc = new PdfDocument();
                // Load a PDF document
                //doc.LoadFromFile("table.PDF");
                string fullPath = Server.MapPath("~/table.pdf");
                doc.LoadFromFile(fullPath);


                // Get the page count of the document
                int pageCount = doc.Pages.Count;

                // Insert a new page into the PDF document as the first page
                PdfPageBase tocPage = doc.Pages.Insert(0);

                // Draw TOC title on the new page
                string title = "Table of Contents";
                PdfTrueTypeFont titleFont = new PdfTrueTypeFont(new Font("Arial", 20, FontStyle.Bold));
                PdfStringFormat centerAlignment = new PdfStringFormat(PdfTextAlignment.Center, PdfVerticalAlignment.Middle);
                PointF location = new PointF(tocPage.Canvas.ClientSize.Width / 2, titleFont.MeasureString(title).Height + 10);
                tocPage.Canvas.DrawString(title, titleFont, PdfBrushes.CornflowerBlue, location, centerAlignment);

                // Draw TOC content on the new page
                PdfTrueTypeFont titlesFont = new PdfTrueTypeFont(new Font("Arial", 14));
                String[] titles = new String[pageCount];
                for (int i = 0; i < titles.Length; i++)
                {
                    titles[i] = string.Format("This is page {0}", i + 1);
                }
                float y = titleFont.MeasureString(title).Height + 10;
                float x = 0;

                // Draw page numbers of the target pages on the new page
                for (int i = 1; i <= pageCount; i++)
                {
                    string text = titles[i - 1];
                    SizeF titleSize = titlesFont.MeasureString(text);

                    PdfPageBase navigatedPage = doc.Pages[i];

                    string pageNumText = (i + 1).ToString();
                    SizeF pageNumTextSize = titlesFont.MeasureString(pageNumText);
                    tocPage.Canvas.DrawString(text, titlesFont, PdfBrushes.CadetBlue, 0, y);
                    float dotLocation = titleSize.Width + 2 + x;
                    float pageNumLocation = tocPage.Canvas.ClientSize.Width - pageNumTextSize.Width;
                    for (float j = dotLocation; j < pageNumLocation; j++)
                    {
                        if (dotLocation >= pageNumLocation)
                        {
                            break;
                        }
                        tocPage.Canvas.DrawString(".", titlesFont, PdfBrushes.Gray, dotLocation, y);
                        dotLocation += 3;
                    }
                    tocPage.Canvas.DrawString(pageNumText, titlesFont, PdfBrushes.CadetBlue, pageNumLocation, y);

                    // Add actions that will take you to the target pages when clicked on to the new page
                    location = new PointF(0, y);
                    RectangleF titleBounds = new RectangleF(location, new SizeF(tocPage.Canvas.ClientSize.Width, titleSize.Height));
                    PdfDestination dest = new PdfDestination(navigatedPage, new PointF(-doc.PageSettings.Margins.Top, -doc.PageSettings.Margins.Left));
                    PdfActionAnnotation action = new PdfActionAnnotation(titleBounds, new PdfGoToAction(dest));
                    action.Border = new PdfAnnotationBorder(0);
                    (tocPage as PdfNewPage).Annotations.Add(action);
                    y += titleSize.Height + 10;
                }

                // Save the PDF document
                string filePath = Server.MapPath("~/TableOfContents.pdf");
                doc.SaveToFile(filePath);
                doc.Close();
                Response.Write("pdf are created sucssecfully!");
            }
            catch (Exception ex)
            {
                Response.Write("PDF are not created");
            }

        }
    }
}




static void Main(string[] args)
        {
            //create a PDF document
            PdfDocument doc = new PdfDocument();
            doc.PageSettings.Size = PdfPageSize.A4;

            //reset the default margins to 0
            doc.PageSettings.Margins = new PdfMargins(0);

            //create a PdfMargins object, the parameters indicate the page margins you want to set
            PdfMargins margins = new PdfMargins(60, 60, 60, 60);

            //create a header template with content and apply it to page template
            doc.Template.Top = CreateHeaderTemplate(doc, margins);

            //apply blank templates to other parts of page template
            doc.Template.Bottom = new PdfPageTemplateElement(doc.PageSettings.Size.Width, margins.Bottom);
            doc.Template.Left = new PdfPageTemplateElement(margins.Left, doc.PageSettings.Size.Height);
            doc.Template.Right = new PdfPageTemplateElement(margins.Right, doc.PageSettings.Size.Height);
        }
        static PdfPageTemplateElement CreateHeaderTemplate(PdfDocument doc, PdfMargins margins)
        {
            //get page size
            SizeF pageSize = doc.PageSettings.Size;

            //create a PdfPageTemplateElement object as header space
            PdfPageTemplateElement headerSpace = new PdfPageTemplateElement(pageSize.Width, margins.Top);
            headerSpace.Foreground = false;

            //declare two float variables
            float x = margins.Left;
            float y = 0;

            //draw image in header space 
            PdfImage headerImage = PdfImage.FromFile("logo.png");
            float width = headerImage.Width / 3;
            float height = headerImage.Height / 3;
            headerSpace.Graphics.DrawImage(headerImage, x, margins.Top - height - 2, width, height);

            //draw line in header space
            PdfPen pen = new PdfPen(PdfBrushes.Gray, 1);
            headerSpace.Graphics.DrawLine(pen, x, y + margins.Top - 2, pageSize.Width - x, y + margins.Top - 2);

            //draw text in header space
            PdfTrueTypeFont font = new PdfTrueTypeFont(new Font("Impact", 25f, FontStyle.Bold));
            PdfStringFormat format = new PdfStringFormat(PdfTextAlignment.Left);
            String headerText = "HEADER TEXT";
            SizeF size = font.MeasureString(headerText, format);
            headerSpace.Graphics.DrawString(headerText, font, PdfBrushes.Gray, pageSize.Width - x - size.Width - 2, margins.Top - (size.Height + 5), format);

            //return headerSpace
            return headerSpace;
        }
















using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace HelloWorld
{
		private bool CreateTOC(string SubjectNo, string foldername, string Subjectinitial)
	{
		FileInfo fInfo = null;
		string PathforLocal = string.Empty;
		int av = 1;
		int ileft = 0;
		int itop = 0;
		int ipages = 0;
		int splitchar = 0;
		ileft = 0;
		itop = 0;
		splitchar = 0;
		ipages = 1;
		object lst1 = null;
		string strtitle = null;
		string strpage = null;
		string siteid = null;
		int i1 = 0;
		strtitle = "";
		strpage = "";
		siteid = "";
		iTextSharp.text.Chunk c = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cPagenumber = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cPagenumberTest = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cDottedline = null;
		List<string> strsub = new List<string>();
		iTextSharp.text.pdf.PdfAction action = null;
		string strcommand = "";

		//Dim strdot As String = ".............................................................................................................................................................."
		try
		{
			if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport")))
			{
				Directory.CreateDirectory(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport"));
			}

			byte[] downloadbytes = System.IO.File.ReadAllBytes(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\Report\\02.pdf");
			iTextSharp.text.pdf.PdfReader reader = new iTextSharp.text.pdf.PdfReader(downloadbytes);
			//List<Dictionary<string, object>> lst = iTextSharp.text.pdf.SimpleBookmark.GetBookmark(reader);
            var lst = iTextSharp.text.pdf.SimpleBookmark.GetBookmark(reader);
            iTextSharp.text.pdf.PdfStamper stamper = new iTextSharp.text.pdf.PdfStamper(reader, new FileStream(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport\\" + SubjectNo + ".pdf", FileMode.Create), '4');
			stamper.Writer.SetPdfVersion(iTextSharp.text.pdf.PdfWriter.PDF_VERSION_1_4); //'Added By ketan
			stamper.InsertPage(1, reader.GetPageSize(1));

			string pagewidth = (reader.GetPageSize(1).Width).ToString();
			itop = Convert.ToInt32(reader.GetPageSize(1).Height - 27);
			iTextSharp.text.pdf.PdfContentByte canvas = stamper.GetOverContent(1);
			string fontpath = Server.MapPath("Reports") + "\\times.ttf";
			iTextSharp.text.pdf.BaseFont customfont = iTextSharp.text.pdf.BaseFont.CreateFont(fontpath, iTextSharp.text.pdf.BaseFont.CP1252, iTextSharp.text.pdf.BaseFont.EMBEDDED);
			iTextSharp.text.Font font1 = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.BLACK);
			iTextSharp.text.Font font2 = new iTextSharp.text.Font(customfont, 12, 0, iTextSharp.text.BaseColor.BLUE);
			iTextSharp.text.Font font3 = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.BLUE);
			iTextSharp.text.Font Whitefont = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.WHITE);
			if (!this.AddHeader(canvas, stamper, reader, itop, 1, SubjectNo, Subjectinitial))
			{
				return false;
			}

			itop -= 140;

			if (lst.Count > 0)
			{
				c = new iTextSharp.text.Chunk("TABLE OF CONTENTS");
				c.Font = font1;
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_CENTER, new iTextSharp.text.Phrase(c), Convert.ToSingle(Convert.ToSingle(pagewidth) / 2), itop, 0);
				Dictionary<string, object> Hashtable1 = new Dictionary<string, object>();
				Hashtable1.Add("Title", "TABLE OF CONTENTS");
				Hashtable1.Add("Page", "1 XYZ 0 685 .00");
				Hashtable1.Add("Action", "GoTo");
				lst.Insert(0, Hashtable1);
			}

			int j2 = 0;
			int ipage = 1;
			int itopcount = itop;
			if (!this.PagesCount(lst, c, ref ileft, ref pagewidth, ref itopcount, ref ipage, ref reader, ref font2, ref font3))
			{
				throw new Exception();
			}
			else
			{
				j2 = ipage;
			}

			for (int i = 0; i < lst.Count; i++)
			{
				strsub.Clear();
				itop -= 20;
				if (itop < 72)
				{
					ipages += 1;
					stamper.InsertPage(ipages, reader.GetPageSize(1));
					canvas = stamper.GetOverContent(ipages);
					itop = Convert.ToInt32(reader.GetPageSize(1).Height - 27);
					if (!this.AddHeader(canvas, stamper, reader, itop, ipages, SubjectNo, Subjectinitial))
					{
						return false;
					}
					itop -= 160;
				}
				else
				{
					canvas = stamper.GetOverContent(ipages);
				}

				ileft = 72;
				dynamic lst2 = lst[i];
				i1 += 1;
				action = new iTextSharp.text.pdf.PdfAction();

				if (lst2.TryGetValue("Title", strtitle))
				{
					c = new iTextSharp.text.Chunk(strtitle);
					c.Font = font3;
					c.SetBackground(iTextSharp.text.BaseColor.WHITE);
					if (c.GetWidthPoint() + ileft > Convert.ToInt32(Convert.ToInt32(pagewidth) - 47))
					{
						if (ileft == 82)
						{
							splitchar = 66;
						}
						else if (ileft == 92)
						{
							splitchar = 65;
						}
						else if (ileft == 102)
						{
							splitchar = 64;
						}
						else if (ileft == 72)
						{
							splitchar = 67;
						}

						string strtemp = Convert.ToString(strtitle.Length / (double)splitchar);
						if (strtitle.Length <= splitchar)
						{
							strtemp = "0";
						}
//INSTANT C# NOTE: The ending condition of VB 'For' loops is tested only on entry to the loop. Instant C# has created a temporary variable in order to use the initial value of Convert.ToInt16(strtemp.Split(".")(0)) for every iteration:
						int tempVar = Convert.ToInt16(strtemp.Split('.')[0]);
						for (int i2 = 0; i2 <= tempVar; i2++)
						{
							if (i2 == 0)
							{
								if (Convert.ToInt16(strtemp.Split('.')[0]) == 0)
								{
									strsub.Add(strtitle.Substring(i2 * splitchar, strtitle.Length));
								}
								else
								{
									strsub.Add(strtitle.Substring(i2 * splitchar, splitchar));
								}
							}
							else
							{
								strsub.Add(strtitle.Substring(i2 * splitchar - 1, strtitle.Length - (i2 * splitchar - 1)));
							}
						}
					}
					else
					{
						strsub.Add(strtitle.Substring(0, strtitle.Length));
					}
				}

				//------------------For Text------------------------------
				action.Put(iTextSharp.text.pdf.PdfName.S, iTextSharp.text.pdf.PdfName.GOTO);
				if (lst2.TryGetValue("Page", strpage))
				{
					strpage = strpage.Replace("XYZ", "/XYZ");

					if (strsub[0].ToUpper() == "TABLE OF CONTENTS")
					{
						action.Put(iTextSharp.text.pdf.PdfName.D, new iTextSharp.text.pdf.PdfLiteral("[" + "0" + " " + strpage.Split(' ')[1] + " " + strpage.Split(' ')[2] + " " + strpage.Split(' ')[3] + " " + strpage.Split(' ')[4] + "]"));
					}
					else
					{
						action.Put(iTextSharp.text.pdf.PdfName.D, new iTextSharp.text.pdf.PdfLiteral("[" + Convert.ToInt32(Convert.ToInt32(strpage.Split(' ')[0]) + j2 - 1).ToString() + " " + strpage.Split(' ')[1] + " " + strpage.Split(' ')[2] + " " + strpage.Split(' ')[3] + " " + strpage.Split(' ')[4] + "]"));
					}
				}

				cDottedline = new iTextSharp.text.Chunk(new iTextSharp.text.pdf.draw.DottedLineSeparator());
				cDottedline.Font = font3;
				// cDottedline.SetAction(action)
				if (strsub.Count == 1)
				{
					//-------------------For Dotted line-------------------------
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cDottedline), ileft, itop, 0);
					//-----------------------------------------------------------
				}
				else
				{
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cDottedline), ileft, itop - ((strsub.Count - 1) * 20), 0);
				}
				for (int i3 = 0; i3 < strsub.Count; i3++)
				{
					if (i3 > 0)
					{
						itop -= 20;
					}
					c = new iTextSharp.text.Chunk(strsub[i3]);
					c.Font = font3;
					c.SetBackground(iTextSharp.text.BaseColor.WHITE);
					c.SetAction(action);
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(c), ileft, itop, 0);
				}
				//-----------------------------------------------------------
				//------------------For page number--------------------------
				int intPageNo = 0;
				string strBlank_PageNo = null;
				if (lst2.TryGetValue("Page", strpage))
				{
					strpage = strpage.Replace("XYZ", "/XYZ");
					if (strsub[0].ToUpper() != "TABLE OF CONTENTS")
					{
						//cPagenumber = New iTextSharp.text.Chunk(Convert.ToString(Convert.ToInt32(strpage.Split(" ")(0)) + j2))
						intPageNo = Convert.ToInt32(strpage.Split(' ')[0]) + j2;
						strBlank_PageNo = "   " + intPageNo;
						cPagenumber = new iTextSharp.text.Chunk(strBlank_PageNo);
					}
					else
					{
						//cPagenumber = New iTextSharp.text.Chunk(Convert.ToString(Convert.ToInt32(strpage.Split(" ")(0))))
						intPageNo = Convert.ToInt32(strpage.Split(' ')[0]);
						strBlank_PageNo = "   " + intPageNo;
						cPagenumber = new iTextSharp.text.Chunk(strBlank_PageNo);
					}
					cPagenumber.Font = font3;
					cPagenumber.SetBackground(iTextSharp.text.BaseColor.WHITE);
				}
				//cPagenumber.SetAction(action)
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cPagenumber), Convert.ToSingle(Convert.ToInt32(pagewidth) - 49), itop, 0);

				int intRemoveExtraWidth = 37;
				intRemoveExtraWidth = intRemoveExtraWidth - (intPageNo.ToString().Length * 5);
				cPagenumberTest = new iTextSharp.text.Chunk(new iTextSharp.text.pdf.draw.DottedLineSeparator());
				cPagenumberTest.Font = Whitefont;
				cPagenumberTest.SetBackground(iTextSharp.text.BaseColor.WHITE);
				//cPagenumberTest.SetAction(action)
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cPagenumberTest), Convert.ToSingle(Convert.ToInt32(pagewidth) - intRemoveExtraWidth), itop, 0);
				//-----------------------------------------------------------
				if (strsub[0].ToUpper() != "TABLE OF CONTENTS")
				{
					lst[i]["Page"] = Convert.ToInt32(strpage.Split(' ')[0] + j2).ToString() + " " + strpage.Split(' ')[1].ToString() + " " + strpage.Split(' ')[2].ToString() + " " + strpage.Split(' ')[3].ToString() + " " + strpage.Split(' ')[4].ToString();
				}

				if (lst2.TryGetValue("Kids", lst1))
				{
					if (!Recursive1(SubjectNo, Subjectinitial, (IList<Dictionary<string, object>>)lst1, ref itop, ref ileft, ref ipages, stamper, reader, canvas, ref j2, ref font2, ref i1))
					{
						throw new Exception();
					}
				}
			}

			stamper.Outlines = lst;
			reader.ViewerPreferences = iTextSharp.text.pdf.PdfWriter.PageModeUseOutlines;

			stamper.Close();
			reader.Close();

			//====================Set pdf fast web view to yes================
			strcommand = Server.MapPath(ConfigurationManager.AppSettings["QPdfPath"].Trim()) + " --linearize " + "\"" + Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport\\" + SubjectNo + ".pdf\" " + "\"" + Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear\\" + SubjectNo + ".pdf\" ";

			if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear")))
			{
				Directory.CreateDirectory(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear"));
			}

			System.Diagnostics.Process.Start("CMD", "/C" + strcommand);
			System.Diagnostics.Process proc = System.Diagnostics.Process.Start("CMD", "/C" + strcommand);
			proc.WaitForExit();
			proc.Close();
			proc.Dispose();
			//===========================================================

			return true;
		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "....CreateTOC", ex);
			return false;
		}
	}
}



















private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
{
    contentPage.Canvas.DrawString(title, new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), point);

    PdfDestination dest = new PdfDestination(contentPage);
    dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

    PdfOutline outline = new PdfOutline(title, dest); // Create PdfOutline with title and destination

    // If the root outline (tocPage.Outlines.Count == 0)
    if (tocPage.Outlines.Count == 0)
    {
        tocPage.Outlines.Add(outline);
    }
    else // Add as child to the last outline
    {
        tocPage.Outlines[tocPage.Outlines.Count - 1].SubPoints.Add(outline);
    }
}







private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
{
    contentPage.Canvas.DrawString(title, new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), point);

    PdfDestination dest = new PdfDestination(contentPage);
    dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

    PdfBookmark bookmark = new PdfBookmark(title); // Use the constructor with title parameter
    bookmark.Destination = dest;

    // If the root bookmark (tocPage.Bookmarks.Count == 0)
    if (tocPage.Bookmarks.Count == 0)
    {
        tocPage.Bookmarks.Add(bookmark);
    }
    else // Add as child to the last bookmark
    {
        tocPage.Bookmarks[tocPage.Bookmarks.Count - 1].SubBookmarks.Add(bookmark);
    }
}





using Spire.Pdf;
using System;
using System.Drawing;
using System.Web.UI;

namespace SpirePdfExample
{
    public partial class Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), new PointF(0, 0), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark();
            bookmark.Title = title;
            tocPage.Bookmarks.Add(bookmark);
        }
    }
}







private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
{
    contentPage.Canvas.DrawString(title, new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), point);

    PdfDestination dest = new PdfDestination(contentPage);
    dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

    PdfBookmark bookmark = new PdfBookmark();
    bookmark.Title = title;
    bookmark.Destination = dest;

    // If the root bookmark (tocPage.Bookmarks.Count == 0)
    if (tocPage.Bookmarks.Count == 0)
    {
        tocPage.Bookmarks.Add(bookmark);
    }
    else // Add as child to the last bookmark
    {
        tocPage.Bookmarks[tocPage.Bookmarks.Count - 1].SubBookmarks.Add(bookmark);
    }
}






using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(document, tocPage, "Chapter " + chapterNumber, contentPage, yPos);
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(document, tocPage, "Section " + chapterNumber + "." + sectionNumber, contentPage, yPos);
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(document, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, contentPage, yPos);
            yPos += 20;
        }

        private void DrawBookmark(PdfDocument document, PdfPageBase tocPage, string title, PdfPageBase contentPage, float yPos)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new PointF(0, yPos));

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - yPos);

            PdfOutlineItem bookmark = new PdfOutlineItem(title);
            bookmark.Destination = dest;
            tocPage.Outlines.Add(bookmark);
        }
    }
}






using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark();
            bookmark.Title = title;
            bookmark.Destination = dest;
            tocPage.Bookmarks.Add(bookmark);
        }
    }
}







using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center; // Corrected the enumeration name here
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark();
            bookmark.Title = title;
            bookmark.Destination = dest;

            tocPage.Bookmarks.Add(bookmark);
        }
    }
}









using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark(title, dest);
            tocPage.Bookmarks.Add(bookmark);
        }
    }
}








<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="SpirePdfExample.Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Generate PDF</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Button ID="btnGeneratePDF" runat="server" Text="Generate PDF" OnClick="btnGeneratePDF_Click" />
        </div>
    </form>
</body>
</html>








using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfStringAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark(title, dest);
            tocPage.Bookmarks.Add(bookmark);
        }
    }
}









using Syncfusion.Pdf;
using Syncfusion.Pdf.Graphics;
using Syncfusion.Pdf.Interactive;
using System.Drawing


PdfDocument document = null;
PdfFont font = null;
PdfBrush brush = null;
float yPos;
private void button1_Click(object sender, EventArgs e)
{
    //Initialize a new instance for PdfDocuemnt
    document = new PdfDocument();
    //Set font for TOC and bookmark contents
    font = new PdfStandardFont(PdfFontFamily.Helvetica, 10f);
    //Set brush for TOC and bookmark contents
    brush = new PdfSolidBrush(Color.Black);
    //Add page for TOC
    PdfSection SectionTOC = document.Sections.Add();
    PdfPage pageTOC = SectionTOC.Pages.Add();
    PdfStringFormat format = new PdfStringFormat(PdfTextAlignment.Center, PdfVerticalAlignment.Middle);
    pageTOC.Graphics.DrawString("Table Of Contents", font, brush, new RectangleF(PointF.Empty, new SizeF(pageTOC.Graphics.ClientSize.Width, 20)), format);
    //Draw contents, bookmarks, and table of contents
    PdfSection SectionContent = document.Sections.Add();
    yPos = 30;
    for (int i = 1; i <= 2; i++)
    {
        PdfPage pageContent = SectionContent.Pages.Add();
        //Add bookmark in PDF document
        PdfBookmark bookmark = AddBookmark(pageContent, pageTOC, "Chapter " + i, new PointF(10, 30));
        //Add sections to bookmark
        PdfBookmark section1 = AddSection(bookmark, pageContent, pageTOC, "Section " + i + ".1", new PointF(30, 50), false);
        //Add subsections to section
        PdfBookmark subsection1 = AddSection(section1, pageContent, pageTOC, "Paragraph " + i + ".1.1", new PointF(50, 70), true);
        PdfBookmark subsection2 = AddSection(section1, pageContent, pageTOC, "Paragraph " + i + ".1.2", new PointF(50, 170), true);
        PdfBookmark subsection3 = AddSection(section1, pageContent, pageTOC, "Paragraph " + i + ".1.3", new PointF(50, 270), true);
        PdfBookmark section2 = AddSection(bookmark, pageContent, pageTOC, "Section " + i + ".2", new PointF(30, 420), false);
        PdfBookmark subsection4 = AddSection(section2, pageContent, pageTOC, "Paragraph " + i + ".2.1", new PointF(50, 440), true);
        PdfBookmark subsection5 = AddSection(section2, pageContent, pageTOC, "Paragraph " + i + ".2.2", new PointF(50, 570), true);
        PdfBookmark subsection6 = AddSection(section2, pageContent, pageTOC, "Paragraph " + i + ".2.3", new PointF(50, 680), true);
    }
    document.Save("TableOfContents.pdf");
    document.Close(true);
}
public PdfBookmark AddBookmark(PdfPage page, PdfPage toc, string title, PointF point)
{
    PdfGraphics graphics = page.Graphics;
    //Add bookmark in PDF document
    PdfBookmark bookmarks = document.Bookmarks.Add(title);
    //Draw the content in the PDF page
    graphics.DrawString(title, font, brush, new PointF(point.X, point.Y));
    //Add table of contents
    AddTableOfcontents(page, toc, title, point);
    //Adding bookmark with named destination
    PdfNamedDestination namedDestination = new PdfNamedDestination(title);
    namedDestination.Destination = new PdfDestination(page, new PointF(point.X, point.Y));
    namedDestination.Destination.Mode = PdfDestinationMode.FitToPage;
    document.NamedDestinationCollection.Add(namedDestination);
    bookmarks.NamedDestination = namedDestination;
    return bookmarks;
}
public PdfBookmark AddSection(PdfBookmark bookmark, PdfPage page, PdfPage toc, string title, PointF point, bool isSubSection)
{
    PdfGraphics graphics = page.Graphics;
    //Add bookmark in PDF document
    PdfBookmark bookmarks = bookmark.Add(title);
    //Draw the content in the PDF page
    graphics.DrawString(title, font, brush, new PointF(point.X, point.Y));
    //Add table of contents
    AddTableOfcontents(page, toc, title, point);
    //Adding bookmark with named destination
    PdfNamedDestination namedDestination = new PdfNamedDestination(title);
    namedDestination.Destination = new PdfDestination(page, new PointF(point.X, point.Y));
    if (isSubSection == true)
        namedDestination.Destination.Zoom = 2f;
    else
        namedDestination.Destination.Zoom = 1f;
    document.NamedDestinationCollection.Add(namedDestination);
    bookmarks.NamedDestination = namedDestination;
    return bookmarks;
}
public void AddTableOfcontents(PdfPage page, PdfPage toc, string title, PointF point)
{
    //Draw title in TOC
    PdfTextElement element = new PdfTextElement(title, font, PdfBrushes.Blue);
    //Set layout format for pagination of TOC
    PdfLayoutFormat format = new PdfLayoutFormat();
    format.Break = PdfLayoutBreakType.FitPage;
    format.Layout = PdfLayoutType.Paginate;
    PdfLayoutResult result = element.Draw(toc, new PointF(point.X, yPos), format);
    //Draw page number in TOC
    PdfTextElement pageNumber = new PdfTextElement(document.Pages.IndexOf(page).ToString(), font, brush);
    pageNumber.Draw(toc, new PointF(toc.Graphics.ClientSize.Width - 40, yPos));
    //Creates a new document link annotation
    RectangleF bounds = result.Bounds;
    bounds.Width = toc.Graphics.ClientSize.Width - point.X;
    PdfDocumentLinkAnnotation documentLinkAnnotation = new PdfDocumentLinkAnnotation(bounds);
    documentLinkAnnotation.AnnotationFlags = PdfAnnotationFlags.NoRotate;
    documentLinkAnnotation.Text = title;
    documentLinkAnnotation.Color = Color.Transparent;
    //Sets the destination
    documentLinkAnnotation.Destination = new PdfDestination(page);
    documentLinkAnnotation.Destination.Location = point;
    //Adds this annotation to a new page
    toc.Annotations.Add(documentLinkAnnotation);
    if (toc != result.Page)
    {
        yPos = result.Bounds.Height + 5;
    }
    else
    {
        yPos += result.Bounds.Height + 5;
    }
    toc = result.Page;
}






















using Spire.Pdf;
using Spire.Pdf.Actions;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace TableOfContents
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //Initialize an instance of the PdfDocument class
            PdfDocument doc = new PdfDocument();
            //Load a PDF document
            doc.LoadFromFile("Sample.PDF");

            //Get the page count of the document
            int pageCount = doc.Pages.Count;

            //Insert a new page into the pdf document as the first page
            PdfPageBase tocPage = doc.Pages.Insert(0);

            //Draw TOC title on the new page
            string title = "Table of Contents";
            PdfTrueTypeFont titleFont = new PdfTrueTypeFont(new Font("Arial", 20, FontStyle.Bold));
            PdfStringFormat centerAlignment = new PdfStringFormat(PdfTextAlignment.Center, PdfVerticalAlignment.Middle);
            PointF location = new PointF(tocPage.Canvas.ClientSize.Width / 2, titleFont.MeasureString(title).Height + 10);
            tocPage.Canvas.DrawString(title, titleFont, PdfBrushes.CornflowerBlue, location, centerAlignment);

            //Draw TOC content on the new page
            PdfTrueTypeFont titlesFont = new PdfTrueTypeFont(new Font("Arial", 14));
            String[] titles = new String[pageCount];
            for (int i = 0; i < titles.Length; i++)
            {
                titles[i] = string.Format("This is page {0}", i + 1);
            }
            float y = titleFont.MeasureString(title).Height + 10;
            float x = 0;

            //Draw page numbers of the target pages on the new page
            for (int i = 1; i <= pageCount; i++)
            {
                string text = titles[i - 1];
                SizeF titleSize = titlesFont.MeasureString(text);

                PdfPageBase navigatedPage = doc.Pages[i];

                string pageNumText = (i + 1).ToString();
                SizeF pageNumTextSize = titlesFont.MeasureString(pageNumText);
                tocPage.Canvas.DrawString(text, titlesFont, PdfBrushes.CadetBlue, 0, y);
                float dotLocation = titleSize.Width + 2 + x;
                float pageNumlocation = tocPage.Canvas.ClientSize.Width - pageNumTextSize.Width;
                for (float j = dotLocation; j < pageNumlocation; j++)
                {
                    if (dotLocation >= pageNumlocation)
                    {
                        break;
                    }
                    tocPage.Canvas.DrawString(".", titlesFont, PdfBrushes.Gray, dotLocation, y);
                    dotLocation += 3;
                }
                tocPage.Canvas.DrawString(pageNumText, titlesFont, PdfBrushes.CadetBlue, pageNumlocation, y);

                //Add actions that will take you to the target pages when clicked on to the new page
                location = new PointF(0, y);
                RectangleF titleBounds = new RectangleF(location, new SizeF(tocPage.Canvas.ClientSize.Width, titleSize.Height));
                PdfDestination Dest = new PdfDestination(navigatedPage, new PointF(-doc.PageSettings.Margins.Top, -doc.PageSettings.Margins.Left));
                PdfActionAnnotation action = new PdfActionAnnotation(titleBounds, new PdfGoToAction(Dest));
                action.Border = new PdfAnnotationBorder(0);
                (tocPage as PdfNewPage).Annotations.Add(action);
                y += titleSize.Height + 10;
            }

            //Save the result pdf document
            doc.SaveToFile("AddTableOfContents.pdf");
            doc.Close();
        }
    }
}

















private bool CreateTOC(string SubjectNo, string foldername, string Subjectinitial)
	{
		FileInfo fInfo = null;
		string PathforLocal = string.Empty;
		int av = 1;
		int ileft = 0;
		int itop = 0;
		int ipages = 0;
		int splitchar = 0;
		ileft = 0;
		itop = 0;
		splitchar = 0;
		ipages = 1;
		object lst1 = null;
		string strtitle = null;
		string strpage = null;
		string siteid = null;
		int i1 = 0;
		strtitle = "";
		strpage = "";
		siteid = "";
		iTextSharp.text.Chunk c = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cPagenumber = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cPagenumberTest = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cDottedline = null;
		List<string> strsub = new List<string>();
		iTextSharp.text.pdf.PdfAction action = null;
		string strcommand = "";

		//Dim strdot As String = ".............................................................................................................................................................."
		try
		{
			if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport")))
			{
				Directory.CreateDirectory(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport"));
			}

			byte[] downloadbytes = System.IO.File.ReadAllBytes(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\Report\\02.pdf");
			iTextSharp.text.pdf.PdfReader reader = new iTextSharp.text.pdf.PdfReader(downloadbytes);
			//List<Dictionary<string, object>> lst = iTextSharp.text.pdf.SimpleBookmark.GetBookmark(reader);
            var lst = iTextSharp.text.pdf.SimpleBookmark.GetBookmark(reader);
            iTextSharp.text.pdf.PdfStamper stamper = new iTextSharp.text.pdf.PdfStamper(reader, new FileStream(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport\\" + SubjectNo + ".pdf", FileMode.Create), '4');
			stamper.Writer.SetPdfVersion(iTextSharp.text.pdf.PdfWriter.PDF_VERSION_1_4); //'Added By ketan
			stamper.InsertPage(1, reader.GetPageSize(1));

			string pagewidth = (reader.GetPageSize(1).Width).ToString();
			itop = Convert.ToInt32(reader.GetPageSize(1).Height - 27);
			iTextSharp.text.pdf.PdfContentByte canvas = stamper.GetOverContent(1);
			string fontpath = Server.MapPath("Reports") + "\\times.ttf";
			iTextSharp.text.pdf.BaseFont customfont = iTextSharp.text.pdf.BaseFont.CreateFont(fontpath, iTextSharp.text.pdf.BaseFont.CP1252, iTextSharp.text.pdf.BaseFont.EMBEDDED);
			iTextSharp.text.Font font1 = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.BLACK);
			iTextSharp.text.Font font2 = new iTextSharp.text.Font(customfont, 12, 0, iTextSharp.text.BaseColor.BLUE);
			iTextSharp.text.Font font3 = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.BLUE);
			iTextSharp.text.Font Whitefont = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.WHITE);
			if (!this.AddHeader(canvas, stamper, reader, itop, 1, SubjectNo, Subjectinitial))
			{
				return false;
			}

			itop -= 140;

			if (lst.Count > 0)
			{
				c = new iTextSharp.text.Chunk("TABLE OF CONTENTS");
				c.Font = font1;
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_CENTER, new iTextSharp.text.Phrase(c), Convert.ToSingle(Convert.ToSingle(pagewidth) / 2), itop, 0);
				Dictionary<string, object> Hashtable1 = new Dictionary<string, object>();
				Hashtable1.Add("Title", "TABLE OF CONTENTS");
				Hashtable1.Add("Page", "1 XYZ 0 685 .00");
				Hashtable1.Add("Action", "GoTo");
				lst.Insert(0, Hashtable1);
			}

			int j2 = 0;
			int ipage = 1;
			int itopcount = itop;
			if (!this.PagesCount(lst, c, ref ileft, ref pagewidth, ref itopcount, ref ipage, ref reader, ref font2, ref font3))
			{
				throw new Exception();
			}
			else
			{
				j2 = ipage;
			}

			for (int i = 0; i < lst.Count; i++)
			{
				strsub.Clear();
				itop -= 20;
				if (itop < 72)
				{
					ipages += 1;
					stamper.InsertPage(ipages, reader.GetPageSize(1));
					canvas = stamper.GetOverContent(ipages);
					itop = Convert.ToInt32(reader.GetPageSize(1).Height - 27);
					if (!this.AddHeader(canvas, stamper, reader, itop, ipages, SubjectNo, Subjectinitial))
					{
						return false;
					}
					itop -= 160;
				}
				else
				{
					canvas = stamper.GetOverContent(ipages);
				}

				ileft = 72;
				dynamic lst2 = lst[i];
				i1 += 1;
				action = new iTextSharp.text.pdf.PdfAction();

				if (lst2.TryGetValue("Title", strtitle))
				{
					c = new iTextSharp.text.Chunk(strtitle);
					c.Font = font3;
					c.SetBackground(iTextSharp.text.BaseColor.WHITE);
					if (c.GetWidthPoint() + ileft > Convert.ToInt32(Convert.ToInt32(pagewidth) - 47))
					{
						if (ileft == 82)
						{
							splitchar = 66;
						}
						else if (ileft == 92)
						{
							splitchar = 65;
						}
						else if (ileft == 102)
						{
							splitchar = 64;
						}
						else if (ileft == 72)
						{
							splitchar = 67;
						}

						string strtemp = Convert.ToString(strtitle.Length / (double)splitchar);
						if (strtitle.Length <= splitchar)
						{
							strtemp = "0";
						}
//INSTANT C# NOTE: The ending condition of VB 'For' loops is tested only on entry to the loop. Instant C# has created a temporary variable in order to use the initial value of Convert.ToInt16(strtemp.Split(".")(0)) for every iteration:
						int tempVar = Convert.ToInt16(strtemp.Split('.')[0]);
						for (int i2 = 0; i2 <= tempVar; i2++)
						{
							if (i2 == 0)
							{
								if (Convert.ToInt16(strtemp.Split('.')[0]) == 0)
								{
									strsub.Add(strtitle.Substring(i2 * splitchar, strtitle.Length));
								}
								else
								{
									strsub.Add(strtitle.Substring(i2 * splitchar, splitchar));
								}
							}
							else
							{
								strsub.Add(strtitle.Substring(i2 * splitchar - 1, strtitle.Length - (i2 * splitchar - 1)));
							}
						}
					}
					else
					{
						strsub.Add(strtitle.Substring(0, strtitle.Length));
					}
				}

				//------------------For Text------------------------------
				action.Put(iTextSharp.text.pdf.PdfName.S, iTextSharp.text.pdf.PdfName.GOTO);
				if (lst2.TryGetValue("Page", strpage))
				{
					strpage = strpage.Replace("XYZ", "/XYZ");

					if (strsub[0].ToUpper() == "TABLE OF CONTENTS")
					{
						action.Put(iTextSharp.text.pdf.PdfName.D, new iTextSharp.text.pdf.PdfLiteral("[" + "0" + " " + strpage.Split(' ')[1] + " " + strpage.Split(' ')[2] + " " + strpage.Split(' ')[3] + " " + strpage.Split(' ')[4] + "]"));
					}
					else
					{
						action.Put(iTextSharp.text.pdf.PdfName.D, new iTextSharp.text.pdf.PdfLiteral("[" + Convert.ToInt32(Convert.ToInt32(strpage.Split(' ')[0]) + j2 - 1).ToString() + " " + strpage.Split(' ')[1] + " " + strpage.Split(' ')[2] + " " + strpage.Split(' ')[3] + " " + strpage.Split(' ')[4] + "]"));
					}
				}

				cDottedline = new iTextSharp.text.Chunk(new iTextSharp.text.pdf.draw.DottedLineSeparator());
				cDottedline.Font = font3;
				// cDottedline.SetAction(action)
				if (strsub.Count == 1)
				{
					//-------------------For Dotted line-------------------------
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cDottedline), ileft, itop, 0);
					//-----------------------------------------------------------
				}
				else
				{
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cDottedline), ileft, itop - ((strsub.Count - 1) * 20), 0);
				}
				for (int i3 = 0; i3 < strsub.Count; i3++)
				{
					if (i3 > 0)
					{
						itop -= 20;
					}
					c = new iTextSharp.text.Chunk(strsub[i3]);
					c.Font = font3;
					c.SetBackground(iTextSharp.text.BaseColor.WHITE);
					c.SetAction(action);
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(c), ileft, itop, 0);
				}
				//-----------------------------------------------------------
				//------------------For page number--------------------------
				int intPageNo = 0;
				string strBlank_PageNo = null;
				if (lst2.TryGetValue("Page", strpage))
				{
					strpage = strpage.Replace("XYZ", "/XYZ");
					if (strsub[0].ToUpper() != "TABLE OF CONTENTS")
					{
						//cPagenumber = New iTextSharp.text.Chunk(Convert.ToString(Convert.ToInt32(strpage.Split(" ")(0)) + j2))
						intPageNo = Convert.ToInt32(strpage.Split(' ')[0]) + j2;
						strBlank_PageNo = "   " + intPageNo;
						cPagenumber = new iTextSharp.text.Chunk(strBlank_PageNo);
					}
					else
					{
						//cPagenumber = New iTextSharp.text.Chunk(Convert.ToString(Convert.ToInt32(strpage.Split(" ")(0))))
						intPageNo = Convert.ToInt32(strpage.Split(' ')[0]);
						strBlank_PageNo = "   " + intPageNo;
						cPagenumber = new iTextSharp.text.Chunk(strBlank_PageNo);
					}
					cPagenumber.Font = font3;
					cPagenumber.SetBackground(iTextSharp.text.BaseColor.WHITE);
				}
				//cPagenumber.SetAction(action)
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cPagenumber), Convert.ToSingle(Convert.ToInt32(pagewidth) - 49), itop, 0);

				int intRemoveExtraWidth = 37;
				intRemoveExtraWidth = intRemoveExtraWidth - (intPageNo.ToString().Length * 5);
				cPagenumberTest = new iTextSharp.text.Chunk(new iTextSharp.text.pdf.draw.DottedLineSeparator());
				cPagenumberTest.Font = Whitefont;
				cPagenumberTest.SetBackground(iTextSharp.text.BaseColor.WHITE);
				//cPagenumberTest.SetAction(action)
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cPagenumberTest), Convert.ToSingle(Convert.ToInt32(pagewidth) - intRemoveExtraWidth), itop, 0);
				//-----------------------------------------------------------
				if (strsub[0].ToUpper() != "TABLE OF CONTENTS")
				{
					lst[i]["Page"] = Convert.ToInt32(strpage.Split(' ')[0] + j2).ToString() + " " + strpage.Split(' ')[1].ToString() + " " + strpage.Split(' ')[2].ToString() + " " + strpage.Split(' ')[3].ToString() + " " + strpage.Split(' ')[4].ToString();
				}

				if (lst2.TryGetValue("Kids", lst1))
				{
					if (!Recursive1(SubjectNo, Subjectinitial, (IList<Dictionary<string, object>>)lst1, ref itop, ref ileft, ref ipages, stamper, reader, canvas, ref j2, ref font2, ref i1))
					{
						throw new Exception();
					}
				}
			}

			stamper.Outlines = lst;
			reader.ViewerPreferences = iTextSharp.text.pdf.PdfWriter.PageModeUseOutlines;

			stamper.Close();
			reader.Close();

			//'Enable if security needs.
			//Dim DocSecurity As Document = New Document(Server.MapPath(ConfigurationManager.AppSettings.Item("uploadfilepath").Trim()) + "\" + Me.HProjectId.Value.ToString() + "\" + foldername + "\Report\" + SubjectNo + "_1" + ".pdf")
			//DocSecurity.LicenseKey = "dfvo+uv66OPj6vrr6PTq+unr9Ovo9OPj4+P66g=="
			//DocSecurity.Security.CanEditContent = False
			//DocSecurity.Save(Server.MapPath(ConfigurationManager.AppSettings.Item("uploadfilepath").Trim()) + "\" + Me.HProjectId.Value.ToString() + "\" + foldername + "\FinalReport\" + SubjectNo + ".pdf")
			//DocSecurity.AutoCloseAppendedDocs = True
			//DocSecurity.Close()

			//====================Set pdf fast web view to yes================
			strcommand = Server.MapPath(ConfigurationManager.AppSettings["QPdfPath"].Trim()) + " --linearize " + "\"" + Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport\\" + SubjectNo + ".pdf\" " + "\"" + Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear\\" + SubjectNo + ".pdf\" ";

			if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear")))
			{
				Directory.CreateDirectory(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear"));
			}

			System.Diagnostics.Process.Start("CMD", "/C" + strcommand);
			System.Diagnostics.Process proc = System.Diagnostics.Process.Start("CMD", "/C" + strcommand);
			proc.WaitForExit();
			proc.Close();
			proc.Dispose();
			//===========================================================

			return true;
		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "....CreateTOC", ex);
			return false;
		}
	}















public bool FindBlankPage(ref string DocRemove, byte[] bytes)
	{
		try
		{
			iTextSharp.text.pdf.PdfReader oreader = new iTextSharp.text.pdf.PdfReader(bytes);
			using (MemoryStream stream = new MemoryStream())
			{
				iTextSharp.text.pdf.PdfReader reader = new iTextSharp.text.pdf.PdfReader(bytes);
				bytes = null;
				for (int i = 1; i <= reader.NumberOfPages; i++)
				{
					object sOut = "";
					iTextSharp.text.pdf.parser.LocationTextExtractionStrategy its = new iTextSharp.text.pdf.parser.LocationTextExtractionStrategy();
					sOut = iTextSharp.text.pdf.parser.PdfTextExtractor.GetTextFromPage(oreader, i, its);
					if (Convert.ToString(sOut) == "")
					{
						DocRemove += (i - 1).ToString() + ",";
					}
				}
				stream.Dispose();
			}
			return true;
		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "Error While Get Blank Page! ", ex);
			return false;
		}
		finally
		{
		}
	}



















public bool GetBlankpage(ref Document d1, Document d2)
	{
		byte[] bytes = null;
		string DocRemove = string.Empty;
		string[] DocRemove_arry = null;
		try
		{
			bytes = d2.Save();
			iTextSharp.text.pdf.PdfReader oreader = new iTextSharp.text.pdf.PdfReader(bytes);

			using (MemoryStream stream = new MemoryStream())
			{
				iTextSharp.text.pdf.PdfReader reader = new iTextSharp.text.pdf.PdfReader(bytes);
				bytes = null;
				using (iTextSharp.text.pdf.PdfStamper stamper = new iTextSharp.text.pdf.PdfStamper(reader, stream))
				{
					for (int i = 1; i <= reader.NumberOfPages; i++)
					{
						object sOut = "";
						iTextSharp.text.pdf.parser.LocationTextExtractionStrategy its = new iTextSharp.text.pdf.parser.LocationTextExtractionStrategy();
						sOut = iTextSharp.text.pdf.parser.PdfTextExtractor.GetTextFromPage(oreader, i, its);
						if (Convert.ToString(sOut) == "")
						{
							DocRemove += (i - 1).ToString() + ",";
						}
					}
				}
				stream.Dispose();
			}

			if (DocRemove.Length > 0)
			{
				DocRemove_arry = DocRemove.Substring(0, DocRemove.Length - 1).Split(',');
				for (int i = DocRemove_arry.Length - 1; i >= 0; i--)
				{
					d1.Pages.Remove(Convert.ToInt32(DocRemove_arry[i]));
				}
			}
			return true;

		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "Error While Get Blank Page! ", ex);
			return false;
		}
		finally
		{
		}
	}












create table of contents in html to pdf with links using asp.net spire.pdf






using Spire.Pdf;
using Spire.Pdf.Graphics;
using Spire.Pdf.Tables;
using System;
using System.Collections.Generic;
using System.Drawing;

namespace PdfTableOfContents
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePdf_Click(object sender, EventArgs e)
        {
            // Create a new PDF document
            PdfDocument doc = new PdfDocument();

            // Add a new page to the document
            PdfPageBase page = doc.Pages.Add();

            // Create a font for the title
            PdfFont fontTitle = new PdfFont(PdfFontFamily.Helvetica, 16f, PdfFontStyle.Bold);

            // Create a font for the table of contents entries
            PdfFont fontTOC = new PdfFont(PdfFontFamily.Helvetica, 12f);

            // Title
            string title = "Sample Document";
            PointF titlePosition = new PointF(50, 50);
            page.Canvas.DrawString(title, fontTitle, PdfBrushes.Black, titlePosition);

            // Generate some sample content with headings
            List<string> headings = new List<string>
            {
                "Introduction",
                "Section 1",
                "Section 2",
                "Conclusion"
            };

            // Store the page numbers of headings
            Dictionary<string, int> tocEntries = new Dictionary<string, int>();

            // Draw the headings and store their page numbers
            float yOffset = 100;
            foreach (string heading in headings)
            {
                yOffset += 20; // Adjust the vertical position for the next heading
                page.Canvas.DrawString(heading, fontTOC, PdfBrushes.Black, new PointF(50, yOffset));
                tocEntries.Add(heading, doc.Pages.Count); // Store the page number of the heading
            }

            // Create a new page for the table of contents
            PdfPageBase tocPage = doc.Pages.Add();

            // Draw the title for the table of contents
            tocPage.Canvas.DrawString("Table of Contents", fontTitle, PdfBrushes.Black, new PointF(50, 50));

            // Draw the table of contents entries
            yOffset = 100;
            foreach (var entry in tocEntries)
            {
                yOffset += 20;
                tocPage.Canvas.DrawString(entry.Key + " - Page " + entry.Value, fontTOC, PdfBrushes.Black, new PointF(50, yOffset));
            }

            // Save the PDF document
            string filePath = Server.MapPath("~/TableOfContents.pdf");
            doc.SaveToFile(filePath);
            doc.Close();

            // Offer the PDF file for download
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }
    }
}









using Spire.Pdf;
using Spire.Pdf.Graphics;
using Spire.Pdf.Tables;
using System;
using System.Collections.Generic;
using System.Drawing;

namespace PdfTableOfContents
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePdf_Click(object sender, EventArgs e)
        {
            // Create a new PDF document
            PdfDocument doc = new PdfDocument();

            // Add a new page to the document
            PdfPageBase page = doc.Pages.Add();

            // Create a font for the title
            PdfFont fontTitle = new PdfFont(PdfFontFamily.Helvetica, 16f, PdfFontStyle.Bold);

            // Create a font for the table of contents entries
            PdfFont fontTOC = new PdfFont(PdfFontFamily.Helvetica, 12f);

            // Title
            string title = "Sample Document";
            PointF titlePosition = new PointF(50, 50);
            page.Canvas.DrawString(title, fontTitle, PdfBrushes.Black, titlePosition);

            // Generate some sample content with headings
            List<string> headings = new List<string>
            {
                "Introduction",
                "Section 1",
                "Section 2",
                "Conclusion"
            };

            // Store the page numbers of headings
            Dictionary<string, int> tocEntries = new Dictionary<string, int>();

            // Draw the headings and store their page numbers
            float yOffset = 100;
            foreach (string heading in headings)
            {
                yOffset += 20; // Adjust the vertical position for the next heading
                page.Canvas.DrawString(heading, fontTOC, PdfBrushes.Black, new PointF(50, yOffset));
                tocEntries.Add(heading, doc.Pages.Count); // Store the page number of the heading
            }

            // Create a new page for the table of contents
            PdfPageBase tocPage = doc.Pages.Add();

            // Draw the title for the table of contents
            tocPage.Canvas.DrawString("Table of Contents", fontTitle, PdfBrushes.Black, new PointF(50, 50));

            // Draw the table of contents entries
            yOffset = 100;
            foreach (var entry in tocEntries)
            {
                yOffset += 20;
                tocPage.Canvas.DrawString(entry.Key + " - Page " + entry.Value, fontTOC, PdfBrushes.Black, new PointF(50, yOffset));
            }

            // Save the PDF document
            doc.Save(Response, "TableOfContents.pdf", ContentDisposition.Attachment, HttpReadType.Open);
            doc.Close();
            Response.End();
        }
    }
}







using Spire.Pdf;
using Spire.Pdf.Graphics;
using Spire.Pdf.Tables;
using System;
using System.Collections.Generic;
using System.Drawing;

public partial class GeneratePdfWithToc : System.Web.UI.Page
{
    protected void btnGeneratePdf_Click(object sender, EventArgs e)
    {
        // Create a new PDF document
        PdfDocument doc = new PdfDocument();

        // Add a page
        PdfPageBase page = doc.Pages.Add();

        // Create a PdfTable for the table of contents
        PdfTable tocTable = new PdfTable();
        tocTable.Style.CellPadding = 2;
        tocTable.Style.DefaultStyle.BackgroundBrush = PdfBrushes.LightGray;
        tocTable.Style.DefaultStyle.Font = new PdfTrueTypeFont(new Font("Arial", 10f), true);
        tocTable.Style.HeaderSource = PdfHeaderSource.Rows;
        tocTable.Style.HeaderRowCount = 1;

        // Define table headers
        tocTable.Headers.Add(1);
        tocTable.Headers[0].Cells[0].Value = "Table of Contents";

        // Add table columns
        tocTable.Columns.Add(200);

        // Define table content
        List<string> tocEntries = new List<string>();
        tocEntries.Add("Chapter 1: Introduction");
        tocEntries.Add("Chapter 2: Getting Started");
        tocEntries.Add("Chapter 3: Advanced Techniques");

        // Add TOC entries to the table
        foreach (string entry in tocEntries)
        {
            PdfRow row = tocTable.Rows.Add();
            row.Cells[0].Value = entry;
        }

        // Draw the TOC table on the page
        tocTable.Draw(page, new PointF(50, 50));

        // Add content after the TOC
        PdfStringFormat format = new PdfStringFormat();
        format.ParagraphIndent = 10;
        PdfFont font = new PdfTrueTypeFont(new Font("Arial", 12f), true);
        page.Canvas.DrawString("Chapter 1: Introduction", font, PdfBrushes.Black, new PointF(50, 200), format);
        page.Canvas.DrawString("This is the content of Chapter 1.", font, PdfBrushes.Black, new PointF(70, 230), format);

        // Save the PDF document
        string filePath = Server.MapPath("~/GeneratedFiles/DocumentWithToc.pdf");
        doc.SaveToFile(filePath);
        doc.Close();

        // Provide the generated PDF file for download
        Response.ContentType = "application/pdf";
        Response.AppendHeader("Content-Disposition", "attachment; filename=DocumentWithToc.pdf");
        Response.TransmitFile(filePath);
        Response.End();
    }
}












<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GeneratePdfWithToc.aspx.cs" Inherits="GeneratePdfWithToc" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Generate PDF with Table of Contents</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Button ID="btnGeneratePdf" runat="server" Text="Generate PDF with TOC" OnClick="btnGeneratePdf_Click" />
        </div>
    </form>
</body>
</html>











using Spire.Pdf;
using Spire.Pdf.HtmlConverter;
using System;
using System.Drawing;
using System.IO;
using System.Threading;

namespace ConvertHtmlStringToPdfWithoutPlugin
{
    public partial class HtmlToPdf : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnConvert_Click(object sender, EventArgs e)
        {
            if (fileUploadHtml.HasFile)
            {
                string fileName = Path.GetFileName(fileUploadHtml.PostedFile.FileName);
                string filePath = Server.MapPath("~/UploadedFiles/") + fileName;
                string pdfFileName = Path.ChangeExtension(fileName, ".pdf");
                string pdfFilePath = Server.MapPath("~/ConvertedFiles/") + pdfFileName;

                // Save uploaded HTML file
                fileUploadHtml.SaveAs(filePath);

                // Create a PdfDocument object
                PdfDocument doc = new PdfDocument();

                // Create a PdfPageSettings object
                PdfPageSettings setting = new PdfPageSettings();

                // Save page size and margins through the object
                setting.Size = new SizeF(1000, 1000);
                setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

                // Create a PdfHtmlLayoutFormat object
                PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

                // Set IsWaiting property to true
                htmlLayoutFormat.IsWaiting = true;

                // Read HTML string from uploaded file
                string htmlString = File.ReadAllText(filePath);

                // Load HTML from HTML string using LoadFromHTML method
                Thread thread = new Thread(() =>
                {
                    doc.LoadFromHTML(htmlString, true, setting, htmlLayoutFormat);
                });
                thread.SetApartmentState(ApartmentState.STA);
                thread.Start();
                thread.Join();

                // Save as a PDF file with the same name as uploaded HTML file
                doc.SaveToFile(pdfFilePath);
                doc.Close();
            }
        }
    }
}







using Spire.Pdf;
using Spire.Pdf.HtmlConverter;
using System;
using System.Drawing;
using System.IO;
using System.Threading;

namespace ConvertHtmlStringToPdfWithoutPlugin
{
    public partial class HtmlToPdf : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnConvert_Click(object sender, EventArgs e)
        {
            //Create a PdfDocument object
            PdfDocument doc = new PdfDocument();

            //Create a PdfPageSettings object
            PdfPageSettings setting = new PdfPageSettings();

            //Save page size and margins through the object
            setting.Size = new SizeF(1000, 1000);
            setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

            //Create a PdfHtmlLayoutFormat object
            PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

            //Set IsWaiting property to true
            htmlLayoutFormat.IsWaiting = true;

            //Read html string from uploaded file
            if (fileUploadHtml.HasFile)
            {
                string fileName = Path.GetFileName(fileUploadHtml.PostedFile.FileName);
                string filePath = Server.MapPath("~/UploadedFiles/") + fileName;
                fileUploadHtml.SaveAs(filePath);

                //Load HTML from html string using LoadFromHTML method
                string htmlString = File.ReadAllText(filePath);

                //Load HTML from html string using LoadFromHTML method
                Thread thread = new Thread(() =>
                { doc.LoadFromHTML(htmlString, true, setting, htmlLayoutFormat); });
                thread.SetApartmentState(ApartmentState.STA);
                thread.Start();
                thread.Join();

                //Save to a PDF file
                doc.SaveToFile(Server.MapPath("~/ConvertedFiles/HtmlToPdf.pdf"));
            }
        }
    }
}










<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="HtmlToPdf.aspx.cs" Inherits="ConvertHtmlStringToPdfWithoutPlugin.HtmlToPdf" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Convert HTML String to PDF</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:FileUpload ID="fileUploadHtml" runat="server" />
            <asp:Button ID="btnConvert" runat="server" Text="Convert to PDF" OnClick="btnConvert_Click" />
        </div>
    </form>
</body>
</html>










using Spire.Pdf;
using Spire.Pdf.HtmlConverter;
using System.IO;
using System.Threading;
using System.Drawing;

namespace ConvertHtmlStringToPdfWithoutPlugin
{
    class Program
    {
        static void Main(string[] args)
        {
            //Create a PdfDocument object
            PdfDocument doc = new PdfDocument();

            //Create a PdfPageSettings object
            PdfPageSettings setting = new PdfPageSettings();

            //Save page size and margins through the object
            setting.Size = new SizeF(1000, 1000);
            setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

            //Create a PdfHtmlLayoutFormat object
            PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

            //Set IsWaiting property to true
            htmlLayoutFormat.IsWaiting = true;

            //Read html string from a .html file
            string htmlString = File.ReadAllText(@"C:\Users\Administrator\Desktop\Document\Html\Sample.html");

            //Load HTML from html string using LoadFromHTML method
            Thread thread = new Thread(() =>
            { doc.LoadFromHTML(htmlString, true, setting, htmlLayoutFormat); });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
            thread.Join();

            //Save to a PDF file
            doc.SaveToFile("HtmlStringToPdf.pdf");
        }
    }
}








using System;
using Spire.Pdf;
using System.Threading;
using Spire.Pdf.HtmlConverter;
using System.Drawing;

namespace SPIREPDF_HTMLtoPDF
{
    public partial class UrlToPdf : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnConvert_Click(object sender, EventArgs e)
        {
            //Create a PdfDocument object
            PdfDocument doc = new PdfDocument();

            //Create a PdfPageSettings object
            PdfPageSettings setting = new PdfPageSettings();

            //Save page size and margins through the object
            setting.Size = new SizeF(1000, 1000);
            setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

            //Create a PdfHtmlLayoutFormat object
            PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

            //Set IsWaiting property to true
            htmlLayoutFormat.IsWaiting = true;

            //Specific the URL path to convert
            String url = "https://www.wikipedia.org/";

            //Load HTML from a URL path using LoadFromHTML method
            Thread thread = new Thread(() =>
            { doc.LoadFromHTML(url, true, true, false, setting, htmlLayoutFormat); });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
            thread.Join();

            //Save the document to a PDF file
            doc.SaveToFile(Server.MapPath("~/UrlToPdf.pdf"));
            doc.Close();
        }
    }
}












<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UrlToPdf.aspx.cs" Inherits="SPIREPDF_HTMLtoPDF.UrlToPdf" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Convert URL to PDF</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Button ID="btnConvert" runat="server" Text="Convert to PDF" OnClick="btnConvert_Click" />
        </div>
    </form>
</body>
</html>














using System;
using Spire.Pdf;
using System.Threading;
using Spire.Pdf.HtmlConverter;
using System.Drawing;

namespace SPIREPDF_HTMLtoPDF
{
    class Program
    {
        static void Main(string[] args)
        {
            //Create a PdfDocument object
            PdfDocument doc = new PdfDocument();

            //Create a PdfPageSettings object
            PdfPageSettings setting = new PdfPageSettings();

            //Save page size and margins through the object
            setting.Size = new SizeF(1000, 1000);
            setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

            //Create a PdfHtmlLayoutFormat object
            PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

            //Set IsWaiting property to true
            htmlLayoutFormat.IsWaiting = true;

            //Specific the URL path to convert
            String url = "https://www.wikipedia.org/";

            //Load HTML from a URL path using LoadFromHTML method
            Thread thread = new Thread(() =>
            { doc.LoadFromHTML(url, true, true, false, setting, htmlLayoutFormat); });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
            thread.Join();

            //Save the document to a PDF file
            doc.SaveToFile("UrlToPdf.pdf");
            doc.Close();
        }
    }
}














CREATE TABLE Customer (
    CustomerId INT PRIMARY KEY,
    CustomerName VARCHAR(255),
    City VARCHAR(255),
    Email VARCHAR(255),
    ContactNumber VARCHAR(20)
);









-- Inserting 10 entries into the Customer table
INSERT INTO Customer (CustomerId, CustomerName, City, Email, ContactNumber) VALUES
(1, 'Rahul Kumar', 'Delhi', 'rahul@example.com', '9876543210'),
(2, 'Priya Sharma', 'Mumbai', 'priya@example.com', '8765432109'),
(3, 'Amit Singh', 'Bangalore', 'amit@example.com', '7654321098'),
(4, 'Anjali Gupta', 'Kolkata', 'anjali@example.com', '6543210987'),
(5, 'Ravi Patel', 'Chennai', 'ravi@example.com', '5432109876'),
(6, 'Sunita Verma', 'Hyderabad', 'sunita@example.com', '4321098765'),
(7, 'Vikas Mishra', 'Pune', 'vikas@example.com', '3210987654'),
(8, 'Neha Reddy', 'Ahmedabad', 'neha@example.com', '2109876543'),
(9, 'Karan Gupta', 'Jaipur', 'karan@example.com', '1098765432'),
(10, 'Pooja Singh', 'Lucknow', 'pooja@example.com', '9876543210');










Server Error in '/' Application.
A potentially dangerous Request.Form value was detected from the client (hfGridHtml="
   <table cellspacing="...").
Description: ASP.NET has detected data in the request that is potentially dangerous because it might include HTML markup or script. The data might represent an attempt to compromise the security of your application, such as a cross-site scripting attack. If this type of input is appropriate in your application, you can include code in a web page to explicitly allow it. For more information, see http://go.microsoft.com/fwlink/?LinkID=212874.

Exception Details: System.Web.HttpRequestValidationException: A potentially dangerous Request.Form value was detected from the client (hfGridHtml="
   <table cellspacing="...").

Source Error:


[No relevant source lines]

Source File: C:\Windows\Microsoft.NET\Framework\v4.0.30319\Temporary ASP.NET Files\root\3abe6c24\2071dd7c\App_Web_h0uybqlo.2.cs    Line: 0







protected void ExportToPDF(object sender, EventArgs e)
{
    // Get the encoded content of hfGridHtml
    string encodedContent = Server.HtmlEncode(Request.Form[hfGridHtml.UniqueID]);

    // Create a StringReader to read the encoded content
    StringReader sr = new StringReader(encodedContent);

    // Create a new PDF document
    Document pdfDoc = new Document(PageSize.A4, 10f, 10f, 10f, 0f);

    // Set up the PdfWriter to write the PDF to the response stream
    PdfWriter writer = PdfWriter.GetInstance(pdfDoc, Response.OutputStream);

    // Open the PDF document
    pdfDoc.Open();

    // Parse the encoded HTML content and add it to the PDF document
    XMLWorkerHelper.GetInstance().ParseXHtml(writer, pdfDoc, sr);

    // Close the PDF document
    pdfDoc.Close();

    // Set the response content type and headers
    Response.ContentType = "application/pdf";
    Response.AddHeader("content-disposition", "attachment;filename=HTML.pdf");
    Response.Cache.SetCacheability(HttpCacheability.NoCache);

    // Write the PDF document to the response stream
    Response.Write(pdfDoc);

    // End the response
    Response.End();
}







An exception of type 'System.Web.HttpRequestValidationException' occurred in System.Web.dll but was not handled in user code

Additional information: A potentially dangerous Request.Form value was detected from the client (hfGridHtml="

    <table cellspacing="...").

 protected void ExportToPDF(object sender, EventArgs e)
        {
            StringReader sr = new StringReader(Request.Form[hfGridHtml.UniqueID]);
            Document pdfDoc = new Document(PageSize.A4, 10f, 10f, 10f, 0f);
            PdfWriter writer = PdfWriter.GetInstance(pdfDoc, Response.OutputStream);
            pdfDoc.Open();
            XMLWorkerHelper.GetInstance().ParseXHtml(writer, pdfDoc, sr);
            pdfDoc.Close();
            Response.ContentType = "application/pdf";
            Response.AddHeader("content-disposition", "attachment;filename=HTML.pdf");
            Response.Cache.SetCacheability(HttpCacheability.NoCache);
            Response.Write(pdfDoc);
            Response.End();
        }









<%@ Page Language="C#" AutoEventWireup="true" CodeFile="YourPageName.aspx.cs" Inherits="YourNamespace.YourPageName" %>

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
                <label for="fileUpload">Upload HTML file:</label>
                <asp:FileUpload ID="fileUpload" runat="server" CssClass="form-control" />
            </div>
            <div class="form-group">
                <label for="firstUrlTextBox">or Enter URL:</label>
                <asp:TextBox ID="firstUrlTextBox" runat="server" CssClass="form-control" TextMode="Url"></asp:TextBox>
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





protected void convertToPdfButton_Click(object sender, EventArgs e)
{
    // Check if URL is provided
    if (!string.IsNullOrEmpty(firstUrlTextBox.Text))
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
            HtmlToPdfElement htmlToPdfElement = new HtmlToPdfElement(0, 0, firstUrlTextBox.Text);

            // Optionally set a delay before conversion to allow asynchronous scripts to finish
            htmlToPdfElement.ConversionDelay = 2;

            // Add the HTML to PDF document
            pdfPage.AddElement(htmlToPdfElement);

            // Save the PDF document to a memory buffer
            byte[] outPdfBuffer = pdfDocument.Save();

            // Generate a unique file name for the PDF
            string fileName = "ConvertedDocument.pdf";

            // Write the PDF document buffer to a file
            File.WriteAllBytes(Server.MapPath("~/PDFFiles/" + fileName), outPdfBuffer);
        }
        finally
        {
            // Close the PDF document
            pdfDocument.Close();
        }

        // Provide a download link for the generated PDF file
        Response.Redirect("~/DownloadPage.aspx");
    }
    else
    {
        // Handle error - URL is not provided
    }
}







An exception of type 'Winnovative.HtmlConvertException' occurred in wnvhtmltopdf.dll but was not handled in user code

Additional information: The URL to convert is null.











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
