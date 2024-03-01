using iText.Kernel.Pdf;
using iText.Kernel.Utils;

namespace PDFMerge
{
    public class PDFMerge
    {
        private static string[] INPUT_FILES = { "/uploads/first.pdf", "/uploads/second.pdf" };
        private static string OUTPUT_FOLDER = "/myfiles/";
        
        static void Main(string[] args)
        {
            MergePDFs(INPUT_FILES, OUTPUT_FOLDER + "merged.pdf");
        }

        public static void MergePDFs(string[] inputFiles, string outputFile)
        {
            using (PdfDocument resultDocument = new PdfDocument(new PdfWriter(outputFile)))
            {
                foreach (string inputFile in inputFiles)
                {
                    using (PdfDocument pdfDocument = new PdfDocument(new PdfReader(inputFile)))
                    {
                        PdfMerger merger = new PdfMerger(resultDocument);
                        merger.Merge(pdfDocument, 1, pdfDocument.GetNumberOfPages());
                    }
                }
            }
        }
    }
}


<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>PDF Merger</title>
<style>
    #drop_zone {
        border: 2px dashed #ccc;
        width: 100%;
        height: 200px;
        text-align: center;
        padding: 50px 0;
        cursor: pointer;
    }
    #file_input {
        display: none;
    }
</style>
</head>
<body>

<div id="drop_zone" ondrop="dropHandler(event)" ondragover="dragOverHandler(event)">
    <p>Drag & drop PDF files here</p>
    <p>or</p>
    <label for="file_input">Click here to select files</label>
    <input type="file" id="file_input" multiple onchange="handleFiles(this.files)">
</div>

<button id="merge_btn" onclick="mergePDFs()">Merge PDFs</button>

<script>
    function dragOverHandler(event) {
        event.preventDefault();
        event.dataTransfer.dropEffect = 'copy';
    }

    function dropHandler(event) {
        event.preventDefault();
        var files = event.dataTransfer.files;
        handleFiles(files);
    }

    function handleFiles(files) {
        for (var i = 0; i < files.length; i++) {
            if (files[i].type === 'application/pdf') {
                // Handle PDF file
                console.log('PDF file:', files[i].name);
            } else {
                alert('Please select only PDF files.');
            }
        }
    }

    function mergePDFs() {
        // Send selected PDF files to server for merging
        // Implement server-side logic to merge PDFs and return the merged PDF file
        alert('Merging PDFs...');
        // Example: Use AJAX to send file data to server
    }
</script>

</body>
</html>




<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sample HTML with Bookmarks and TOC</title>
</head>
<body>
    <h1 id="section1">Section 1</h1>
    <p>This is the content of section 1.</p>

    <h2 id="subSection1">Subsection 1.1</h2>
    <p>This is the content of subsection 1.1.</p>

    <h2 id="subSection2">Subsection 1.2</h2>
    <p>This is the content of subsection 1.2.</p>

    <h1 id="section2">Section 2</h1>
    <p>This is the content of section 2.</p>

    <h2 id="subSection3">Subsection 2.1</h2>
    <p>This is the content of subsection 2.1.</p>

    <h2 id="subSection4">Subsection 2.2</h2>
    <p>This is the content of subsection 2.2.</p>
</body>
</html>

using iText.Kernel.Pdf;
using iText.Layout;
using iText.Layout.Element;
using iText.Layout.Properties;
using iText.Html2pdf;

namespace PdfWithBookmarkAndTOC
{
    public class PdfGenerator
    {
        public static void GeneratePdfWithBookmarkAndTOC(string htmlContent, string outputPath)
        {
            // Convert HTML to PDF
            PdfDocument pdfDocument = new PdfDocument(new PdfWriter(outputPath));
            ConverterProperties converterProperties = new ConverterProperties();
            HtmlConverter.ConvertToPdf(htmlContent, pdfDocument, converterProperties);

            // Access PDF document
            Document document = new Document(pdfDocument);

            // Add bookmarks and TOC
            AddBookmarksAndTOC(document);

            // Close the document
            document.Close();
        }

        private static void AddBookmarksAndTOC(Document document)
        {
            // Iterate through document and add bookmarks for headings
            foreach (IBlockElement element in document.GetRenderer().GetModelElement().GetChildren())
            {
                if (element is Paragraph paragraph && paragraph.GetFirstRenderer() is ParagraphRenderer renderer)
                {
                    if (renderer.GetPropertyAsBoolean(Property.FIRST_PARAGRAPH) && paragraph.HasOwnProperty(Property.TITLE))
                    {
                        string title = paragraph.GetProperty(Property.TITLE).ToString();
                        document.Add(new Bookmark(title).AddDestinationPageOnly());
                    }
                }
            }

            // Generate table of contents
            document.Add(new AreaBreak(AreaBreakType.NEXT_PAGE));
            document.Add(new Paragraph("Table of Contents").SetTextAlignment(TextAlignment.CENTER).SetBold().SetFontSize(16));
            foreach (IBlockElement element in document.GetRenderer().GetModelElement().GetChildren())
            {
                if (element is Paragraph paragraph && paragraph.GetFirstRenderer() is ParagraphRenderer renderer)
                {
                    if (renderer.GetPropertyAsBoolean(Property.FIRST_PARAGRAPH) && paragraph.HasOwnProperty(Property.TITLE))
                    {
                        string title = paragraph.GetProperty(Property.TITLE).ToString();
                        document.Add(new Paragraph().Add(title).SetAction(PdfAction.CreateGoTo(title)));
                    }
                }
            }
        }
    }
}


You tried signing in with a different authentication method than the one you used during signup. Please try again using your original authentication method.

