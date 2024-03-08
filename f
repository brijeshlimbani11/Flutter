using Spire.Pdf;
using Spire.Pdf.Graphics;
using Spire.Pdf.Bookmarks;
using System;
using System.Collections.Generic;
using System.IO;

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
    PdfTextElement c = new PdfTextElement();
    PdfTextElement cPagenumber = new PdfTextElement();
    PdfTextElement cPagenumberTest = new PdfTextElement();
    PdfTextElement cDottedline = null;
    List<string> strsub = new List<string>();
    PdfAction action = null;
    string strcommand = "";

    try
    {
        if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport")))
        {
            Directory.CreateDirectory(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport"));
        }

        byte[] downloadbytes = File.ReadAllBytes(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\Report\\02.pdf");
        PdfDocument reader = new PdfDocument(downloadbytes);
        var lst = reader.Bookmarks;

        PdfDocument stamper = new PdfDocument();

        stamper.LoadFromFile(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport\\" + SubjectNo + ".pdf");
        stamper.Pages.Insert(0, reader.Pages[0]);

        string pagewidth = reader.Pages[0].Size.Width.ToString();
        itop = (int)reader.Pages[0].Size.Height - 27;

        PdfPageBase canvas = stamper.Pages[0];

        string fontpath = Server.MapPath("Reports") + "\\times.ttf";
        PdfTrueTypeFont customfont = new PdfTrueTypeFont(new Font(fontpath, 12f));
        PdfTrueTypeFont font1 = new PdfTrueTypeFont(new Font(customfont, FontStyle.Bold), true);
        PdfTrueTypeFont font2 = new PdfTrueTypeFont(new Font(customfont, FontStyle.Regular), true);
        PdfTrueTypeFont font3 = new PdfTrueTypeFont(new Font(customfont, FontStyle.Bold), true);
        PdfTrueTypeFont Whitefont = new PdfTrueTypeFont(new Font(customfont, FontStyle.Bold), true, BaseColor.White);

        if (!AddHeader(canvas, stamper, reader, itop, 1, SubjectNo, Subjectinitial))
        {
            return false;
        }

        itop -= 140;

        if (lst.Count > 0)
        {
            c = new PdfTextElement("TABLE OF CONTENTS", font1);
            c.Draw(canvas, new PointF((float)reader.Pages[0].Size.Width / 2, itop));
            BookmarkItem item = new BookmarkItem("TABLE OF CONTENTS");
            reader.Bookmarks.Add(item);
        }

        int j2 = 0;
        int ipage = 1;
        int itopcount = itop;

        if (!PagesCount(lst, c, ref ileft, ref pagewidth, ref itopcount, ref ipage, reader, font2, font3))
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
                stamper.Pages.Insert(ipages, reader.Pages[0]);
                canvas = stamper.Pages[ipages];
                itop = (int)reader.Pages[0].Size.Height - 27;

                if (!AddHeader(canvas, stamper, reader, itop, ipages, SubjectNo, Subjectinitial))
                {
                    return false;
                }
                itop -= 160;
            }
            else
            {
                canvas = stamper.Pages[ipages];
            }

            ileft = 72;
            var lst2 = lst[i];
            i1 += 1;
            action = new PdfGoToAction();

            if (lst2.TryGetValue("Title", out strtitle))
            {
                c = new PdfTextElement(strtitle, font3);
                c.SetBackgroundBrush(PdfBrushes.White);
                
                // Adjust font size and position if necessary
                
                c.Draw(canvas, new PointF(ileft, itop));
                if (c.Width + ileft > Convert.ToInt32(Convert.ToInt32(pagewidth) - 47))
                {
                    // Split text if it exceeds page width
                    // Adjust font size and position if necessary
                }
            }

            if (lst2.TryGetValue("Page", out strpage))
            {
                strpage = strpage.Replace("XYZ", "/XYZ");

                // Set action for the bookmark
                // Adjust page number if necessary
                
                if (strsub[0].ToUpper() == "TABLE OF CONTENTS")
                {
                    action.Destination = new PdfDestination(0);
                }
                else
                {
                    action.Destination = new PdfDestination(Convert.ToInt32(strpage.Split(' ')[0]) + j2 - 1);
                }
            }

            if (lst2.TryGetValue("Kids", out lst1))
            {
                if (!Recursive1(SubjectNo, Subjectinitial, (IList<Dictionary<string, object>>)lst1, ref itop, ref ileft, ref ipages, stamper, reader, canvas, ref j2, ref font2, ref i1))
                {
                    throw new Exception();
                }
            }
        }

        stamper.Bookmark = lst;
        reader.ViewerPreferences.PageMode = PdfPageMode.UseOutlines;

        stamper.SaveToFile(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport\\" + SubjectNo + ".pdf");
        stamper.Close();

        // Set PDF Fast Web View to yes
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

        return true;
    }
    catch (Exception ex)
    {
        this.ShowErrorMessage(ex.Message, "....CreateTOC", ex);
        return false;
    }
}
