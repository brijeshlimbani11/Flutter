using Spire.Pdf;
using Spire.Pdf.Graphics;
using System;
using System.IO;

public bool GetBlankpage(ref PdfDocument d1, PdfDocument d2)
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

            using (PdfDocumentBase oreader = PdfReader.Open(bytes))
            {
                for (int i = 0; i < oreader.Pages.Count; i++)
                {
                    string sOut = "";
                    PdfTextExtractionStrategy its = new PdfTextExtractionStrategy();
                    sOut = its.ExtractText(oreader.Pages[i]);
                    if (string.IsNullOrEmpty(sOut.Trim()))
                    {
                        DocRemove += i + ",";
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
        // Handle the exception
        return false;
    }
    finally
    {
        // Clean up resources
    }
}


using Spire.Pdf;
using System;
using System.IO;

public bool FindBlankPage(ref string DocRemove, byte[] bytes)
{
    try
    {
        using (MemoryStream stream = new MemoryStream(bytes))
        {
            using (PdfDocumentBase reader = PdfReader.Open(bytes))
            {
                for (int i = 0; i < reader.Pages.Count; i++)
                {
                    string sOut = "";
                    PdfTextExtractionStrategy its = new PdfTextExtractionStrategy();
                    sOut = its.ExtractText(reader.Pages[i]);
                    if (string.IsNullOrEmpty(sOut.Trim()))
                    {
                        DocRemove += i + ",";
                    }
                }
            }
        }
        return true;
    }
    catch (Exception ex)
    {
        // Handle the exception
        return false;
    }
    finally
    {
        // Clean up resources if needed
    }
}


