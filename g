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
