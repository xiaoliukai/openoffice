/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


#ifndef _SVX_WGHTITEM_HXX
#define _SVX_WGHTITEM_HXX

#include <bf_svtools/bf_solar.h>

// include ---------------------------------------------------------------

#ifndef _VCL_VCLENUM_HXX
#include <vcl/vclenum.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <bf_svtools/eitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

namespace rtl
{
	class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;

// class SvxWeightItem ---------------------------------------------------

/* [Beschreibung]

	Dieses Item beschreibt die Font-Staerke.
*/

class SvxWeightItem : public SfxEnumItem
{
public:
	TYPEINFO();

	SvxWeightItem(  const FontWeight eWght = WEIGHT_NORMAL,
					const USHORT nId = ITEMID_WEIGHT );

	// "pure virtual Methoden" vom SfxPoolItem + SfxEnumItem

	virtual SfxPoolItem*	Clone( SfxItemPool *pPool = 0 ) const;
	virtual SfxPoolItem*	Create(SvStream &, USHORT) const;
	virtual SvStream&		Store(SvStream &, USHORT nItemVersion) const;
	virtual USHORT			GetValueCount() const;

	virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
	virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

	virtual int 			HasBoolValue() const;
	virtual BOOL			GetBoolValue() const;

	inline SvxWeightItem& operator=(const SvxWeightItem& rWeight) {
			SetValue( rWeight.GetValue() );
			return *this;
		}

	// enum cast
	FontWeight				GetWeight() const
								{ return (FontWeight)GetValue(); }
	void					SetWeight( FontWeight eNew )
								{ SetValue( (USHORT)eNew ); }
};

}//end of namespace binfilter
#endif // #ifndef _SVX_WGHTITEM_HXX
