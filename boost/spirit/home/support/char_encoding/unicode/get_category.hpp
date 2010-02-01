/*=============================================================================
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    Autogenerated by MultiStageTable.py (Unicode multi-stage
    table builder) (c) Peter Kankowski, 2008
==============================================================================*/
#if !defined(BOOST_SPIRIT_UNICODE_GET_CATEGORY)
#include <boost/cstdint.hpp>
#include "tables.hpp"

namespace boost { namespace spirit { namespace unicode
{
    // bit pattern: xxMMMCCC
    // MMM: major_category
    // CCC: category
    
    struct properties
    {
        enum major_category 
        {
            letter,
            mark,
            number,
            separator,
            other,
            punctuation,
            symbol
        };
        
        enum category
        {
            uppercase_letter = 0,   // [Lu] an uppercase letter
            lowercase_letter,       // [Ll] a lowercase letter 
            titlecase_letter,       // [Lt] a digraphic character, with first part uppercase 
            modifier_letter,        // [Lm] a modifier letter 
            other_letter,           // [Lo] other letters, including syllables and ideographs
                                    
            nonspacing_mark = 8,    // [Mn] a nonspacing combining mark (zero advance width)
            enclosing_mark,         // [Me] an enclosing combining mark
            spacing_mark,           // [Mc] a spacing combining mark (positive advance width)   
                                    
            decimal_number = 16,    // [Nd] a decimal digit 
            letter_number,          // [Nl] a letterlike numeric character
            other_number,           // [No] a numeric character of other type
                                    
            space_separator = 24,   // [Zs] a space character (of various non-zero widths)
            line_separator,         // [Zl] U+2028 LINE SEPARATOR only 
            paragraph_separator,    // [Zp] U+2029 PARAGRAPH SEPARATOR only
                                    
            control = 32,           // [Cc] a C0 or C1 control code
            format,                 // [Cf] a format control character
            private_use,            // [Co] a private-use character
            surrogate,              // [Cs] a surrogate code point
            unassigned,             // [Cn] a reserved unassigned code point or a noncharacter
                                    
            dash_punctuation = 40,  // [Pd] a dash or hyphen punctuation mark
            open_punctuation,       // [Ps] an opening punctuation mark (of a pair)  
            close_punctuation,      // [Pe] a closing punctuation mark (of a pair)  
            connector_punctuation,  // [Pc] a connecting punctuation mark, like a tie 
            other_punctuation,      // [Po] a punctuation mark of other type 
            initial_punctuation,    // [Pi] an initial quotation mark 
            final_punctuation,      // [Pf] a final quotation mark
                                    
            math_symboll = 48,      // [Sm] a symbol of primarily mathematical use
            currency_symbol,        // [Sc] a currency sign 
            modifier_symbol,        // [Sk] a non-letterlike modifier symbol
            other_symbol            // [So] a symbol of other type 
        };
        
        enum derived_properties
        {
            alphabetic = 64,
            uppercase = 128,
            lowercase = 256,
            white_space = 512,
            noncharacter_code_point = 1024,
            default_ignorable_code_point = 2048
        };
    };

    namespace detail
    {
        inline ::boost::uint16_t category_lookup(::boost::uint32_t ch)
        {
            const ::boost::uint32_t block_size = 256;
            ::boost::uint32_t block_offset = detail::category_stage1[ch / block_size] * block_size;
            ::boost::uint8_t r = detail::category_stage2[block_offset + ch % block_size];
            return r;
        }
    }    
        
    inline category get_category(::boost::uint32_t ch)
    {
        return static_cast<properties::category>(detail::category_lookup(r) & 0x3F);
    }
    
    inline major_category get_major_category(::boost::uint32_t ch)
    {
        return static_cast<properties::major_category>(get_category(ch) >> 3);
    }
    
    inline bool is_alphabetic(::boost::uint32_t ch)
    {
        return detail::category_lookup(r) & properties::alphabetic;
    }
    
    inline bool is_uppercase(::boost::uint32_t ch)
    {
        return detail::category_lookup(r) & properties::uppercase;
    }
    
    inline bool is_lowercase(::boost::uint32_t ch)
    {
        return detail::category_lookup(r) & properties::lowercase;
    }
    
    inline bool is_white_space(::boost::uint32_t ch)
    {
        return detail::category_lookup(r) & properties::white_space;
    }
    
    inline bool is_noncharacter_code_poin(::boost::uint32_t ch)
    {
        return detail::category_lookup(r) & properties::noncharacter_code_point;
    }
    
    inline bool is_default_ignorable_code_point(::boost::uint32_t ch)
    {
        return detail::category_lookup(r) & properties::default_ignorable_code_point;
    }
    
}}}

#endif
