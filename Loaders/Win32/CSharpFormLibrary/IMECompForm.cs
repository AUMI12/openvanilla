using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace CSharpFormLibrary
{
	/// <summary>
	/// Summary description for IMECompForm.
	/// </summary>
	public class IMECompForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox textBox1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		private const int WM_MOUSEACTIVATE = 0x0021;
		private const int MA_NOACTIVATE=0x0003;
		private System.Windows.Forms.Label label1;
		private const int MA_NOACTIVATEANDEAT = 0x0004;

		//private int caretWidth = 0;
        //just give the caret a small point;
        private int caretWidth = 2;
        private int CurrentAll = 0;

		public IMECompForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}
		protected override void WndProc(ref Message m) 
		{
			if (m.Msg == WM_MOUSEACTIVATE) 
			{
				m.Result = (IntPtr)MA_NOACTIVATEANDEAT;
				return;
			}
			base.WndProc(ref m);
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.BackColor = System.Drawing.Color.PapayaWhip;
			this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.textBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.textBox1.Font = new System.Drawing.Font("PMingLiU", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(136)));
			this.textBox1.Location = new System.Drawing.Point(0, 0);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(159, 31);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "textBox1";
			this.textBox1.WordWrap = false;
			// 
			// label1
			// 
			this.label1.BackColor = System.Drawing.SystemColors.WindowFrame;
			this.label1.Location = new System.Drawing.Point(0, 23);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(2, 6);
			this.label1.TabIndex = 1;
			this.label1.Text = "label1";
			// 
			// IMECompForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(9, 24);
			this.BackColor = System.Drawing.SystemColors.Window;
			this.ClientSize = new System.Drawing.Size(159, 27);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.textBox1);
			this.Font = new System.Drawing.Font("PMingLiU", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(136)));
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.Name = "IMECompForm";
			this.Opacity = 0.85;
			this.ShowInTaskbar = false;
			this.ResumeLayout(false);

		}
		#endregion
		public void ShowNoActive()
		{
			UtilFuncs.SetVisibleNoActivate(this, true); // true to show. 
		}
		public void HideNoActive()
		{
			UtilFuncs.SetVisibleNoActivate(this, false); // false to hide.  
		}
		public void ClearComp()
		{
			this.textBox1.Clear();
		}
		public void SetLocation(int x, int y)
		{
			this.Location = new Point(x,y);
		}
		public void SetComp(string inputs)
		{

			if(inputs==null) return;
            //if (inputs == null || this.textBox1.Text == inputs) return;

/* *** Comments due to OVIME.VC8.sln <Jaimie> *************
 * *** postpone this merge until fully upgrade to VC8 *****
			Graphics g = this.textBox1.CreateGraphics();
            Size s;
            Size proposedSize1 = new Size();
            TextFormatFlags tff1;

//1st method for get the exact composition length
#if true           
            System.Drawing.StringFormat format  = new System.Drawing.StringFormat ();

            System.Drawing.RectangleF rect = new System.Drawing.RectangleF(0, 0, 1000, 1000);
            
            System.Drawing.CharacterRange[] ranges  = 
             { new System.Drawing.CharacterRange(0, inputs.Length) };
            System.Drawing.Region[] regions = new System.Drawing.Region[1];

            format.SetMeasurableCharacterRanges (ranges);       

            regions = g.MeasureCharacterRanges (inputs, this.textBox1.Font, rect, format);
            rect    = regions[0].GetBounds (g);

            this.Width = (int)(rect.Right + 1.0f);
#endif
 
//2nd method for getting the exact comp string length
#if false 
            const int width = 32;

            System.Drawing.Bitmap bitmap = new System.Drawing.Bitmap(width, 1, g);
            System.Drawing.SizeF size = g.MeasureString(inputs, this.textBox1.Font);
            System.Drawing.Graphics anagra = System.Drawing.Graphics.FromImage(bitmap);

            int measured_width = (int)size.Width;

            if (anagra != null)
            {
                anagra.Clear(Color.White);
                anagra.DrawString(inputs+"|", this.textBox1.Font, Brushes.Black,
                                                   width - measured_width, -this.textBox1.Font.Height / 2);
                for (int i = width - 1; i >= 0; i--)
                {
                    measured_width--;
                    if (bitmap.GetPixel(i, 0).R != 255)    // found a non-white pixel ?
                        break;
                }
            }

            this.Width = measured_width;
#endif

//3rd method to set textFormatFlags.NoPadding

            tff1 = TextFormatFlags.NoPadding;
            //proposedSize1.Height = this.textBox1.Height;
            //proposedSize1.Height = this.textBox1.Font.Height;
            //proposedSize1.Width = this.textBox1.Width;
            
			//int width = (int)g.MeasureString(inputs, this.textBox1.Font).Width;
  
            s = TextRenderer.MeasureText(g, inputs, this.textBox1.Font, proposedSize1, tff1);
            //this.Width = s.Width;
            //if (inputs.Length == 1)
            {
                //caretWidth = this.Size.Width;
                //caretWidth = measured_width / (inputs.Length);

                CurrentAll = inputs.Length;
            }

			g.Dispose(); 
 * ********************************************************/			
			//string[] a_inputs = inputs.Split(' ');			

            this.textBox1.Text = inputs;
		}

		public void SetCaretX(int x)
		{

            //caretWidth = this.textBox1.Width;
            /* *** Comments due to OVIME.VC8.sln <Jaimie> *************
             * *** postpone this merge until fully upgrade to VC8 ***** 
                        //this.label1.Width = this.Width / CurrentAll;
                        //caretWidth = 2;
                        //this.label1.Width = caretWidth;
                        //�`���׭n���H���P�r�ƪ�����
                        //this.label1.Left = ((this.Width)*(x)/CurrentAll);
             * ********************************************************/
            this.label1.Height = 2;

		}
	}
}
